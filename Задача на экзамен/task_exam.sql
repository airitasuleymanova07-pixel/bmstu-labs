-- Создаем базу данных
CREATE DATABASE shop_db 
WITH 
    ENCODING = 'UTF8'
    LC_COLLATE = 'en_US.UTF-8'
    LC_CTYPE = 'en_US.UTF-8'
    TEMPLATE = template0;

-- Создаем пользователя для приложения 
CREATE USER shop_user WITH PASSWORD 'shop_password';

-- Даем права
GRANT ALL PRIVILEGES ON DATABASE shop_db TO shop_user;

-- Подключаемся к новой базе
\c shop_db

-- Даем права на схему public
GRANT ALL ON SCHEMA public TO shop_user;
GRANT ALL PRIVILEGES ON ALL TABLES IN SCHEMA public TO shop_user;
GRANT ALL PRIVILEGES ON ALL SEQUENCES IN SCHEMA public TO shop_user;

-- Проверяем
SELECT 'Database shop_db created successfully' as message;