#include <iostream>
#include <memory>
#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <stdexcept>
#include <algorithm>
#include <pqxx/pqxx>

using std::string;
using std::vector;
using std::unique_ptr;
using std::make_unique;
using std::map;
using std::runtime_error;
using std::invalid_argument;
using std::tuple;
using std::cout;
using std::cerr;
using std::endl;

enum class OrderStatus {
    PENDING, PROCESSING, SHIPPED, DELIVERED, CANCELLED, RETURNED, REFUNDED
};

string orderStatusToString(OrderStatus status) {
    switch (status) {
        case OrderStatus::PENDING: return "PENDING";
        case OrderStatus::PROCESSING: return "PROCESSING";
        case OrderStatus::SHIPPED: return "SHIPPED";
        case OrderStatus::DELIVERED: return "DELIVERED";
        case OrderStatus::CANCELLED: return "CANCELLED";
        case OrderStatus::RETURNED: return "RETURNED";
        case OrderStatus::REFUNDED: return "REFUNDED";
        default: return "UNKNOWN";
    }
}

OrderStatus stringToOrderStatus(const string& str) {
    if (str == "PENDING") return OrderStatus::PENDING;
    if (str == "PROCESSING") return OrderStatus::PROCESSING;
    if (str == "SHIPPED") return OrderStatus::SHIPPED;
    if (str == "DELIVERED") return OrderStatus::DELIVERED;
    if (str == "CANCELLED") return OrderStatus::CANCELLED;
    if (str == "RETURNED") return OrderStatus::RETURNED;
    if (str == "REFUNDED") return OrderStatus::REFUNDED;
    throw invalid_argument("Invalid order status string");
}

class DatabaseConnection {
private:
    unique_ptr<pqxx::connection> connection;
    string connectionString;
    
public:
    DatabaseConnection(const string& connStr) : connectionString(connStr) {
        try {
            connection = make_unique<pqxx::connection>(connStr);
            if (!connection->is_open()) {
                throw runtime_error("Failed to connect to database");
            }
            cout << "✓ Connected to database successfully\n";
            initializeDatabase();
        } catch (const std::exception& e) {
            cerr << "✗ Connection error: " << e.what() << endl;
            cerr << "Connection string: " << connStr << endl;
            throw;
        }
    }
    
    ~DatabaseConnection() {
        if (connection && connection->is_open()) {
            connection->close();
            cout << "Database connection closed\n";
        }
    }
    
    void initializeDatabase() {
        try {
            pqxx::work txn(*connection);
            cout << "Initializing database tables...\n";
            
            // Users table
            txn.exec(R"(
                CREATE TABLE IF NOT EXISTS users (
                    id SERIAL PRIMARY KEY,
                    username VARCHAR(50) UNIQUE NOT NULL,
                    email VARCHAR(100) UNIQUE NOT NULL,
                    password_hash VARCHAR(255) NOT NULL,
                    role VARCHAR(20) NOT NULL CHECK (role IN ('customer', 'admin', 'manager')),
                    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
                )
            )");
            cout << "  ✓ Created 'users' table\n";
            
            // Products table
            txn.exec(R"(
                CREATE TABLE IF NOT EXISTS products (
                    id SERIAL PRIMARY KEY,
                    name VARCHAR(100) NOT NULL,
                    description TEXT,
                    price DECIMAL(10,2) NOT NULL CHECK (price >= 0),
                    stock_quantity INTEGER NOT NULL CHECK (stock_quantity >= 0),
                    category VARCHAR(50),
                    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
                    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
                )
            )");
            cout << "  ✓ Created 'products' table\n";
            
            // Orders table
            txn.exec(R"(
                CREATE TABLE IF NOT EXISTS orders (
                    id SERIAL PRIMARY KEY,
                    user_id INTEGER REFERENCES users(id),
                    status VARCHAR(20) NOT NULL CHECK (status IN ('PENDING', 'PROCESSING', 'SHIPPED', 'DELIVERED', 'CANCELLED', 'RETURNED', 'REFUNDED')),
                    total_amount DECIMAL(10,2) NOT NULL CHECK (total_amount >= 0),
                    shipping_address TEXT NOT NULL,
                    created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
                    updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
                )
            )");
            cout << "  ✓ Created 'orders' table\n";
            
            // Order items table
            txn.exec(R"(
                CREATE TABLE IF NOT EXISTS order_items (
                    id SERIAL PRIMARY KEY,
                    order_id INTEGER REFERENCES orders(id) ON DELETE CASCADE,
                    product_id INTEGER REFERENCES products(id),
                    quantity INTEGER NOT NULL CHECK (quantity > 0),
                    price DECIMAL(10,2) NOT NULL CHECK (price >= 0)
                )
            )");
            cout << "  ✓ Created 'order_items' table\n";
            
            // Price audit table
            txn.exec(R"(
                CREATE TABLE IF NOT EXISTS price_audit (
                    id SERIAL PRIMARY KEY,
                    product_id INTEGER REFERENCES products(id),
                    old_price DECIMAL(10,2),
                    new_price DECIMAL(10,2),
                    changed_by INTEGER REFERENCES users(id),
                    changed_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
                )
            )");
            cout << "  ✓ Created 'price_audit' table\n";
            
            // Order status audit table
            txn.exec(R"(
                CREATE TABLE IF NOT EXISTS order_status_audit (
                    id SERIAL PRIMARY KEY,
                    order_id INTEGER REFERENCES orders(id),
                    old_status VARCHAR(20),
                    new_status VARCHAR(20),
                    changed_by INTEGER REFERENCES users(id),
                    changed_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP
                )
            )");
            cout << "  ✓ Created 'order_status_audit' table\n";
            
            createTriggersAndFunctions(txn);
            
            txn.commit();
            cout << "✓ Database initialized successfully\n";
        } catch (const std::exception& e) {
            cerr << "✗ Database initialization error: " << e.what() << endl;
            throw;
        }
    }
    
    void createTriggersAndFunctions(pqxx::work& txn) {
        try {
            cout << "Creating triggers and functions...\n";
            
            txn.exec(R"(
                CREATE OR REPLACE FUNCTION update_updated_at_column()
                RETURNS TRIGGER AS $$
                BEGIN
                    NEW.updated_at = CURRENT_TIMESTAMP;
                    RETURN NEW;
                END;
                $$ language 'plpgsql';
            )");
            
            txn.exec(R"(
                DROP TRIGGER IF EXISTS update_products_updated_at ON products;
                CREATE TRIGGER update_products_updated_at
                    BEFORE UPDATE ON products
                    FOR EACH ROW
                    EXECUTE FUNCTION update_updated_at_column();
            )");
            
            txn.exec(R"(
                DROP TRIGGER IF EXISTS update_orders_updated_at ON orders;
                CREATE TRIGGER update_orders_updated_at
                    BEFORE UPDATE ON orders
                    FOR EACH ROW
                    EXECUTE FUNCTION update_updated_at_column();
            )");
            
            txn.exec(R"(
                CREATE OR REPLACE FUNCTION audit_price_change()
                RETURNS TRIGGER AS $$
                BEGIN
                    IF OLD.price != NEW.price THEN
                        INSERT INTO price_audit (product_id, old_price, new_price, changed_by)
                        VALUES (OLD.id, OLD.price, NEW.price, 1);
                    END IF;
                    RETURN NEW;
                END;
                $$ language 'plpgsql';
            )");
            
            txn.exec(R"(
                DROP TRIGGER IF EXISTS audit_product_price ON products;
                CREATE TRIGGER audit_product_price
                    AFTER UPDATE OF price ON products
                    FOR EACH ROW
                    EXECUTE FUNCTION audit_price_change();
            )");
            
            txn.exec(R"(
                CREATE OR REPLACE FUNCTION audit_order_status_change()
                RETURNS TRIGGER AS $$
                BEGIN
                    IF OLD.status != NEW.status THEN
                        INSERT INTO order_status_audit (order_id, old_status, new_status, changed_by)
                        VALUES (OLD.id, OLD.status, NEW.status, 1);
                    END IF;
                    RETURN NEW;
                END;
                $$ language 'plpgsql';
            )");
            
            txn.exec(R"(
                DROP TRIGGER IF EXISTS audit_order_status ON orders;
                CREATE TRIGGER audit_order_status
                    AFTER UPDATE OF status ON orders
                    FOR EACH ROW
                    EXECUTE FUNCTION audit_order_status_change();
            )");
            
            cout << "  ✓ Triggers and functions created\n";
        } catch (const std::exception& e) {
            cerr << "✗ Error creating triggers: " << e.what() << endl;
            throw;
        }
    }
    
    pqxx::connection* getConnection() const {
        return connection.get();
    }
    
    template<typename Func>
    auto executeTransaction(Func func) -> decltype(func(std::declval<pqxx::transaction<>>&())) {
        pqxx::work txn(*connection);
        try {
            auto result = func(txn);
            txn.commit();
            return result;
        } catch (const std::exception& e) {
            txn.abort();
            throw runtime_error("Transaction failed: " + string(e.what()));
        }
    }
};

class Product {
private:
    int id;
    string name;
    string description;
    double price;
    int stockQuantity;
    string category;
    
public:
    Product(int id, const string& name, const string& description,
            double price, int stockQuantity, const string& category)
        : id(id), name(name), description(description), price(price),
          stockQuantity(stockQuantity), category(category) {}
    
    int getId() const { return id; }
    string getName() const { return name; }
    string getDescription() const { return description; }
    double getPrice() const { return price; }
    int getStockQuantity() const { return stockQuantity; }
    string getCategory() const { return category; }
    
    void setPrice(double newPrice) { price = newPrice; }
    void setStockQuantity(int quantity) { stockQuantity = quantity; }
    
    bool isAvailable() const { return stockQuantity > 0; }
    void reduceStock(int quantity) { 
        if (quantity <= stockQuantity) {
            stockQuantity -= quantity; 
        } else {
            throw runtime_error("Insufficient stock");
        }
    }
    void increaseStock(int quantity) { stockQuantity += quantity; }
    
    void saveToDatabase(pqxx::work& txn) const {
        if (id == 0) {
            auto result = txn.exec_params(
                "INSERT INTO products (name, description, price, stock_quantity, category) "
                "VALUES ($1, $2, $3, $4, $5) RETURNING id",
                name, description, price, stockQuantity, category
            );
            const_cast<Product*>(this)->id = result[0][0].as<int>();
        } else {
            txn.exec_params(
                "UPDATE products SET name=$1, description=$2, price=$3, "
                "stock_quantity=$4, category=$5 WHERE id=$6",
                name, description, price, stockQuantity, category, id
            );
        }
    }
    
    static unique_ptr<Product> loadFromDatabase(pqxx::work& txn, int productId) {
        auto result = txn.exec_params(
            "SELECT id, name, description, price, stock_quantity, category "
            "FROM products WHERE id = $1",
            productId
        );
        
        if (result.empty()) {
            return nullptr;
        }
        
        return make_unique<Product>(
            result[0][0].as<int>(),
            result[0][1].as<string>(),
            result[0][2].as<string>(),
            result[0][3].as<double>(),
            result[0][4].as<int>(),
            result[0][5].as<string>()
        );
    }
};

class User {
protected:
    int id;
    string username;
    string email;
    string passwordHash;
    string role;
    
public:
    User(int id, const string& username, const string& email,
         const string& passwordHash, const string& role)
        : id(id), username(username), email(email), passwordHash(passwordHash), role(role) {}
    
    virtual ~User() = default;
    
    virtual bool canViewOrders() const = 0;
    virtual bool canCreateOrder() const = 0;
    virtual bool canCancelOrder() const = 0;
    virtual bool canReturnOrder() const = 0;
    virtual bool canUpdateOrderStatus() const = 0;
    virtual bool canManageProducts() const = 0;
    
    int getId() const { return id; }
    string getUsername() const { return username; }
    string getEmail() const { return email; }
    string getRole() const { return role; }
    
    void saveToDatabase(pqxx::work& txn) const {
        if (id == 0) {
            auto result = txn.exec_params(
                "INSERT INTO users (username, email, password_hash, role) "
                "VALUES ($1, $2, $3, $4) RETURNING id",
                username, email, passwordHash, role
            );
            const_cast<User*>(this)->id = result[0][0].as<int>();
        } else {
            txn.exec_params(
                "UPDATE users SET username=$1, email=$2, password_hash=$3, role=$4 WHERE id=$5",
                username, email, passwordHash, role, id
            );
        }
    }
    
    static unique_ptr<User> createUser(int id, const string& username,
                                      const string& email,
                                      const string& passwordHash,
                                      const string& role) {
        if (role == "customer") {
            return make_unique<Customer>(id, username, email, passwordHash);
        } else if (role == "admin") {
            return make_unique<Admin>(id, username, email, passwordHash);
        } else if (role == "manager") {
            return make_unique<Manager>(id, username, email, passwordHash);
        }
        throw invalid_argument("Invalid role: " + role);
    }
    
    static unique_ptr<User> loadFromDatabase(pqxx::work& txn, int userId) {
        auto result = txn.exec_params(
            "SELECT id, username, email, password_hash, role FROM users WHERE id = $1",
            userId
        );
        
        if (result.empty()) {
            return nullptr;
        }
        
        return createUser(
            result[0][0].as<int>(),
            result[0][1].as<string>(),
            result[0][2].as<string>(),
            result[0][3].as<string>(),
            result[0][4].as<string>()
        );
    }
};

class Customer : public User {
public:
    Customer(int id, const string& username, const string& email,
             const string& passwordHash)
        : User(id, username, email, passwordHash, "customer") {}
    
    bool canViewOrders() const override { return true; }
    bool canCreateOrder() const override { return true; }
    bool canCancelOrder() const override { return true; }
    bool canReturnOrder() const override { return true; }
    bool canUpdateOrderStatus() const override { return false; }
    bool canManageProducts() const override { return false; }
};

class Admin : public User {
public:
    Admin(int id, const string& username, const string& email,
          const string& passwordHash)
        : User(id, username, email, passwordHash, "admin") {}
    
    bool canViewOrders() const override { return true; }
    bool canCreateOrder() const override { return true; }
    bool canCancelOrder() const override { return true; }
    bool canReturnOrder() const override { return true; }
    bool canUpdateOrderStatus() const override { return true; }
    bool canManageProducts() const override { return true; }
};

class Manager : public User {
public:
    Manager(int id, const string& username, const string& email,
            const string& passwordHash)
        : User(id, username, email, passwordHash, "manager") {}
    
    bool canViewOrders() const override { return true; }
    bool canCreateOrder() const override { return false; }
    bool canCancelOrder() const override { return false; }
    bool canReturnOrder() const override { return false; }
    bool canUpdateOrderStatus() const override { return true; }
    bool canManageProducts() const override { return true; }
};

struct OrderItem {
    int productId;
    string productName;
    int quantity;
    double price;
    
    double totalPrice() const { return quantity * price; }
    
    void saveToDatabase(pqxx::work& txn, int orderId) const {
        txn.exec_params(
            "INSERT INTO order_items (order_id, product_id, quantity, price) "
            "VALUES ($1, $2, $3, $4)",
            orderId, productId, quantity, price
        );
    }
};

class Order {
private:
    int id;
    int userId;
    OrderStatus status;
    double totalAmount;
    string shippingAddress;
    vector<OrderItem> items;
    
public:
    Order(int id, int userId, OrderStatus status, double totalAmount,
          const string& shippingAddress)
        : id(id), userId(userId), status(status), totalAmount(totalAmount),
          shippingAddress(shippingAddress) {}
    
    int getId() const { return id; }
    int getUserId() const { return userId; }
    OrderStatus getStatus() const { return status; }
    double getTotalAmount() const { return totalAmount; }
    string getShippingAddress() const { return shippingAddress; }
    const vector<OrderItem>& getItems() const { return items; }
    
    void addItem(const OrderItem& item) {
        items.push_back(item);
        totalAmount += item.totalPrice();
    }
    
    void updateStatus(OrderStatus newStatus, int changedByUserId, pqxx::work& txn) {
        OrderStatus oldStatus = status;
        status = newStatus;
        
        txn.exec_params(
            "UPDATE orders SET status = $1 WHERE id = $2",
            orderStatusToString(status), id
        );
        
        txn.exec_params(
            "INSERT INTO order_status_audit (order_id, old_status, new_status, changed_by) "
            "VALUES ($1, $2, $3, $4)",
            id, orderStatusToString(oldStatus), orderStatusToString(newStatus), changedByUserId
        );
    }
    
    bool cancel(int userId, pqxx::work& txn) {
        if (status == OrderStatus::PENDING || status == OrderStatus::PROCESSING) {
            updateStatus(OrderStatus::CANCELLED, userId, txn);
            
            for (const auto& item : items) {
                txn.exec_params(
                    "UPDATE products SET stock_quantity = stock_quantity + $1 WHERE id = $2",
                    item.quantity, item.productId
                );
            }
            return true;
        }
        return false;
    }
    
    bool returnOrder(int userId, pqxx::work& txn) {
        if (status == OrderStatus::DELIVERED) {
            updateStatus(OrderStatus::RETURNED, userId, txn);
            
            for (const auto& item : items) {
                txn.exec_params(
                    "UPDATE products SET stock_quantity = stock_quantity + $1 WHERE id = $2",
                    item.quantity, item.productId
                );
            }
            return true;
        }
        return false;
    }
    
    void saveToDatabase(pqxx::work& txn) {
        if (id == 0) {
            auto result = txn.exec_params(
                "INSERT INTO orders (user_id, status, total_amount, shipping_address) "
                "VALUES ($1, $2, $3, $4) RETURNING id",
                userId, orderStatusToString(status), totalAmount, shippingAddress
            );
            id = result[0][0].as<int>();
            
            for (const auto& item : items) {
                item.saveToDatabase(txn, id);
            }
        } else {
            txn.exec_params(
                "UPDATE orders SET status=$1, total_amount=$2, shipping_address=$3 WHERE id=$4",
                orderStatusToString(status), totalAmount, shippingAddress, id
            );
            
            txn.exec_params("DELETE FROM order_items WHERE order_id = $1", id);
            for (const auto& item : items) {
                item.saveToDatabase(txn, id);
            }
        }
    }
    
    static unique_ptr<Order> loadFromDatabase(pqxx::work& txn, int orderId) {
        auto orderResult = txn.exec_params(
            "SELECT id, user_id, status, total_amount, shipping_address FROM orders WHERE id = $1",
            orderId
        );
        
        if (orderResult.empty()) {
            return nullptr;
        }
        
        auto order = make_unique<Order>(
            orderResult[0][0].as<int>(),
            orderResult[0][1].as<int>(),
            stringToOrderStatus(orderResult[0][2].as<string>()),
            orderResult[0][3].as<double>(),
            orderResult[0][4].as<string>()
        );
        
        auto itemsResult = txn.exec_params(
            "SELECT oi.product_id, p.name, oi.quantity, oi.price "
            "FROM order_items oi "
            "JOIN products p ON oi.product_id = p.id "
            "WHERE oi.order_id = $1",
            orderId
        );
        
        for (const auto& row : itemsResult) {
            OrderItem item;
            item.productId = row[0].as<int>();
            item.productName = row[1].as<string>();
            item.quantity = row[2].as<int>();
            item.price = row[3].as<double>();
            order->addItem(item);
        }
        
        return order;
    }
};

class ShopSystem {
private:
    unique_ptr<DatabaseConnection> db;
    
public:
    ShopSystem(const string& connectionString) {
        db = make_unique<DatabaseConnection>(connectionString);
    }
    
    unique_ptr<User> createUser(const string& username, const string& email,
                               const string& password, const string& role) {
        return db->executeTransaction([&](pqxx::work& txn) {
            string passwordHash = "hashed_" + password;
            
            auto user = User::createUser(0, username, email, passwordHash, role);
            user->saveToDatabase(txn);
            cout << "✓ Created user: " << username << " (" << role << ")\n";
            return user;
        });
    }
    
    unique_ptr<Product> createProduct(const string& name, const string& description,
                                     double price, int stockQuantity, const string& category) {
        return db->executeTransaction([&](pqxx::work& txn) {
            auto product = make_unique<Product>(0, name, description, price, stockQuantity, category);
            product->saveToDatabase(txn);
            cout << "✓ Created product: " << name << " ($" << price << ")\n";
            return product;
        });
    }
    
    unique_ptr<Order> createOrder(int userId, const vector<OrderItem>& items,
                                 const string& shippingAddress) {
        return db->executeTransaction([&](pqxx::work& txn) {
            for (const auto& item : items) {
                auto productResult = txn.exec_params(
                    "SELECT stock_quantity, price FROM products WHERE id = $1",
                    item.productId
                );
                
                if (productResult.empty()) {
                    throw runtime_error("Product not found: " + std::to_string(item.productId));
                }
                
                int stock = productResult[0][0].as<int>();
                if (stock < item.quantity) {
                    throw runtime_error("Insufficient stock for product ID: " + std::to_string(item.productId));
                }
            }
            
            double totalAmount = 0;
            for (const auto& item : items) {
                auto priceResult = txn.exec_params(
                    "SELECT price FROM products WHERE id = $1",
                    item.productId
                );
                double price = priceResult[0][0].as<double>();
                totalAmount += price * item.quantity;
            }
            
            auto order = make_unique<Order>(0, userId, OrderStatus::PENDING, 
                                          totalAmount, shippingAddress);
            
            for (const auto& item : items) {
                OrderItem orderItem = item;
                auto priceResult = txn.exec_params(
                    "SELECT price, name FROM products WHERE id = $1",
                    item.productId
                );
                orderItem.price = priceResult[0][0].as<double>();
                orderItem.productName = priceResult[0][1].as<string>();
                order->addItem(orderItem);
                
                txn.exec_params(
                    "UPDATE products SET stock_quantity = stock_quantity - $1 WHERE id = $2",
                    item.quantity, item.productId
                );
            }
            
            order->saveToDatabase(txn);
            cout << "✓ Created order #" << order->getId() << " total: $" << totalAmount << "\n";
            return order;
        });
    }
    
    bool updateOrderStatus(int orderId, OrderStatus newStatus, int changedByUserId) {
        return db->executeTransaction([&](pqxx::work& txn) {
            auto order = Order::loadFromDatabase(txn, orderId);
            if (!order) {
                cout << "✗ Order not found: " << orderId << "\n";
                return false;
            }
            
            auto user = User::loadFromDatabase(txn, changedByUserId);
            if (!user || !user->canUpdateOrderStatus()) {
                throw runtime_error("User does not have permission to update order status");
            }
            
            order->updateStatus(newStatus, changedByUserId, txn);
            cout << "✓ Updated order #" << orderId << " status to: " 
                 << orderStatusToString(newStatus) << "\n";
            return true;
        });
    }
    
    bool cancelOrder(int orderId, int userId) {
        return db->executeTransaction([&](pqxx::work& txn) {
            auto order = Order::loadFromDatabase(txn, orderId);
            if (!order) {
                cout << "✗ Order not found: " << orderId << "\n";
                return false;
            }
            
            auto user = User::loadFromDatabase(txn, userId);
            if (!user || !user->canCancelOrder()) {
                throw runtime_error("User does not have permission to cancel order");
            }
            
            if (order->getUserId() != userId && user->getRole() != "admin") {
                throw runtime_error("User can only cancel their own orders");
            }
            
            bool result = order->cancel(userId, txn);
            if (result) {
                cout << "✓ Cancelled order #" << orderId << "\n";
            } else {
                cout << "✗ Cannot cancel order #" << orderId << " (invalid status)\n";
            }
            return result;
        });
    }
    
    bool returnOrder(int orderId, int userId) {
        return db->executeTransaction([&](pqxx::work& txn) {
            auto order = Order::loadFromDatabase(txn, orderId);
            if (!order) {
                cout << "✗ Order not found: " << orderId << "\n";
                return false;
            }
            
            auto user = User::loadFromDatabase(txn, userId);
            if (!user || !user->canReturnOrder()) {
                throw runtime_error("User does not have permission to return order");
            }
            
            if (order->getUserId() != userId) {
                throw runtime_error("User can only return their own orders");
            }
            
            bool result = order->returnOrder(userId, txn);
            if (result) {
                cout << "✓ Returned order #" << orderId << "\n";
            } else {
                cout << "✗ Cannot return order #" << orderId << " (not delivered)\n";
            }
            return result;
        });
    }
    
    bool updateProductPrice(int productId, double newPrice, int userId) {
        return db->executeTransaction([&](pqxx::work& txn) {
            auto user = User::loadFromDatabase(txn, userId);
            if (!user || !user->canManageProducts()) {
                throw runtime_error("User does not have permission to manage products");
            }
            
            txn.exec_params(
                "UPDATE products SET price = $1 WHERE id = $2",
                newPrice, productId
            );
            
            txn.exec_params(
                "UPDATE price_audit SET changed_by = $1 "
                "WHERE id = (SELECT MAX(id) FROM price_audit WHERE product_id = $2)",
                userId, productId
            );
            
            cout << "✓ Updated product #" << productId << " price to: $" << newPrice << "\n";
            return true;
        });
    }
    
    vector<tuple<string, string, string, string>> getOrderStatusHistory(int orderId) {
        return db->executeTransaction([&](pqxx::work& txn) {
            auto result = txn.exec_params(
                "SELECT old_status, new_status, u.username, changed_at "
                "FROM order_status_audit osa "
                "JOIN users u ON osa.changed_by = u.id "
                "WHERE order_id = $1 "
                "ORDER BY changed_at DESC",
                orderId
            );
            
            vector<tuple<string, string, string, string>> history;
            for (const auto& row : result) {
                history.emplace_back(
                    row[0].as<string>(),
                    row[1].as<string>(),
                    row[2].as<string>(),
                    row[3].as<string>()
                );
            }
            return history;
        });
    }
    
    vector<tuple<double, double, string, string>> getProductPriceHistory(int productId) {
        return db->executeTransaction([&](pqxx::work& txn) {
            auto result = txn.exec_params(
                "SELECT old_price, new_price, u.username, changed_at "
                "FROM price_audit pa "
                "JOIN users u ON pa.changed_by = u.id "
                "WHERE product_id = $1 "
                "ORDER BY changed_at DESC",
                productId
            );
            
            vector<tuple<double, double, string, string>> history;
            for (const auto& row : result) {
                history.emplace_back(
                    row[0].as<double>(),
                    row[1].as<double>(),
                    row[2].as<string>(),
                    row[3].as<string>()
                );
            }
            return history;
        });
    }
    
    void showDatabaseStats() {
        db->executeTransaction([&](pqxx::work& txn) {
            cout << "\n=== DATABASE STATISTICS ===\n";
            
            auto users = txn.exec("SELECT COUNT(*) FROM users");
            cout << "Users: " << users[0][0].as<int>() << "\n";
            
            auto products = txn.exec("SELECT COUNT(*) FROM products");
            cout << "Products: " << products[0][0].as<int>() << "\n";
            
            auto orders = txn.exec("SELECT COUNT(*) FROM orders");
            cout << "Orders: " << orders[0][0].as<int>() << "\n";
            
            auto audits = txn.exec("SELECT COUNT(*) FROM order_status_audit");
            cout << "Status audits: " << audits[0][0].as<int>() << "\n";
            
            auto priceAudits = txn.exec("SELECT COUNT(*) FROM price_audit");
            cout << "Price audits: " << priceAudits[0][0].as<int>() << "\n";
        });
    }
};

int main() {
    cout << "=== ONLINE SHOP SYSTEM ===\n";
    cout << "Using OOP, Smart Pointers, and PostgreSQL\n\n";
    
    try {
        // ⚠️ ИЗМЕНИТЕ ЭТУ СТРОКУ ПОД ВАШУ БАЗУ ДАННЫХ!
        string connStr = "dbname=shop_db user=postgres password=your_password host=localhost port=5432";
        
        // Для тестирования - выводим строку подключения (без пароля для безопасности)
        cout << "Connection: " << connStr.substr(0, connStr.find("password=") + 9) << "*******\n";
        
        ShopSystem shop(connStr);
        
        // Демонстрация
        cout << "\n--- DEMONSTRATION ---\n";
        
        // 1. Создание пользователей
        auto customer = shop.createUser("john_doe", "john@example.com", "pass123", "customer");
        auto admin = shop.createUser("shop_admin", "admin@shop.com", "admin123", "admin");
        auto manager = shop.createUser("shop_mgr", "manager@shop.com", "mgr123", "manager");
        
        // 2. Создание продуктов
        auto laptop = shop.createProduct("Gaming Laptop", "High-end gaming laptop", 1500.00, 10, "Electronics");
        auto phone = shop.createProduct("Smartphone", "Latest smartphone model", 999.99, 25, "Electronics");
        auto book = shop.createProduct("C++ Programming", "Learn C++ programming", 49.99, 100, "Books");
        
        // 3. Создание заказа
        vector<OrderItem> items = {
            {laptop->getId(), "", 1, 0},
            {phone->getId(), "", 1, 0}
        };
        
        auto order = shop.createOrder(customer->getId(), items, "123 Main St, City");
        
        // 4. Обновление статуса заказа
        shop.updateOrderStatus(order->getId(), OrderStatus::PROCESSING, admin->getId());
        shop.updateOrderStatus(order->getId(), OrderStatus::SHIPPED, admin->getId());
        
        // 5. Отмена заказа
        shop.cancelOrder(order->getId(), customer->getId());
        
        // 6. Обновление цены продукта
        shop.updateProductPrice(laptop->getId(), 1450.00, manager->getId());
        
        // 7. Показать историю
        cout << "\n--- ORDER STATUS HISTORY ---\n";
        auto statusHistory = shop.getOrderStatusHistory(order->getId());
        for (const auto& [oldStatus, newStatus, changedBy, changedAt] : statusHistory) {
            cout << oldStatus << " → " << newStatus << " by " << changedBy 
                 << " at " << changedAt << "\n";
        }
        
        // 8. Показать историю цен
        cout << "\n--- PRODUCT PRICE HISTORY ---\n";
        auto priceHistory = shop.getProductPriceHistory(laptop->getId());
        for (const auto& [oldPrice, newPrice, changedBy, changedAt] : priceHistory) {
            cout << "$" << oldPrice << " → $" << newPrice << " by " << changedBy 
                 << " at " << changedAt << "\n";
        }
        
        // 9. Статистика базы данных
        shop.showDatabaseStats();
        
        cout << "\n=== DEMONSTRATION COMPLETED SUCCESSFULLY ===\n";
        
    } catch (const std::exception& e) {
        cerr << "\n✗ ERROR: " << e.what() << endl;
        cerr << "\nTROUBLESHOOTING:\n";
        cerr << "1. Check if PostgreSQL is running\n";
        cerr << "2. Check connection string parameters\n";
        cerr << "3. Check if database 'shop_db' exists\n";
        cerr << "4. Check username/password\n";
        return 1;
    }
    
    return 0;
}