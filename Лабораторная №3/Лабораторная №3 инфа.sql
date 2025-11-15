
-- Таблица авторов
CREATE TABLE authors (
    id SERIAL PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    birth_year INTEGER
);

-- Таблица книг
CREATE TABLE books (
    id SERIAL PRIMARY KEY,
    title VARCHAR(200) NOT NULL,
    author_id INTEGER NOT NULL,
    publication_year INTEGER,
    genre VARCHAR(50),
    FOREIGN KEY (author_id) REFERENCES authors(id)
);

-- Таблица пользователей
CREATE TABLE users (
    id SERIAL PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    registration_date DATE NOT NULL
);

-- Таблица выданных книг
CREATE TABLE borrowed_books (
    id SERIAL PRIMARY KEY,
    user_id INTEGER NOT NULL,
    book_id INTEGER NOT NULL,
    borrow_date DATE NOT NULL,
    return_date DATE,
    FOREIGN KEY (user_id) REFERENCES users(id),
    FOREIGN KEY (book_id) REFERENCES books(id)
);

-- 4. ДОБАВЛЕНИЕ ДАННЫХ

-- Добавление авторов
INSERT INTO authors (name, birth_year) VALUES
('Лев Толстой', 1828),
('Фёдор Достоевский', 1821),
('Антон Чехов', 1860);

-- Добавление книг
INSERT INTO books (title, author_id, publication_year, genre) VALUES
('Война и мир', 1, 1869, 'Роман'),
('Анна Каренина', 1, 1877, 'Роман'),
('Преступление и наказание', 2, 1866, 'Психологический роман'),
('Идиот', 2, 1869, 'Роман'),
('Вишнёвый сад', 3, 1904, 'Пьеса'),
('Чайка', 3, 1896, 'Пьеса');

-- Добавление пользователей
INSERT INTO users (name, registration_date) VALUES
('Иван Петров', '2023-01-15'),
('Мария Сидорова', '2023-02-20'),
('Алексей Козлов', '2023-03-10');

-- Добавление записей о выданных книгах
INSERT INTO borrowed_books (user_id, book_id, borrow_date, return_date) VALUES
(1, 1, '2024-01-10', '2024-01-25'),
(2, 3, '2024-01-12', '2024-01-30'),
(3, 5, '2024-02-01', NULL),  -- книга еще не возвращена
(1, 2, '2024-02-05', NULL);  -- книга еще не возвращена

-- 5. ЗАПРОСЫ

-- Запрос 1: Список всех книг определенного автора (Льва Толстого)
SELECT b.title, b.publication_year, b.genre
FROM books b
JOIN authors a ON b.author_id = a.id
WHERE a.name = 'Лев Толстой';

-- Запрос 2: Поиск книг по определенному жанру (Роман)
SELECT b.title, a.name as author, b.publication_year
FROM books b
JOIN authors a ON b.author_id = a.id
WHERE b.genre = 'Роман';

-- Запрос 3: Список пользователей, зарегистрированных в определенный период
SELECT name, registration_date
FROM users
WHERE registration_date BETWEEN '2023-01-01' AND '2023-02-28'
ORDER BY registration_date;

-- Запрос 4: Список книг, которые были взяты и еще не возвращены
SELECT b.title, a.name as author, u.name as user_name, bb.borrow_date
FROM borrowed_books bb
JOIN books b ON bb.book_id = b.id
JOIN authors a ON b.author_id = a.id
JOIN users u ON bb.user_id = u.id
WHERE bb.return_date IS NULL;

-- 6. ДОПОЛНИТЕЛЬНЫЕ ЗАДАНИЯ

-- Отчет о количестве книг, взятых каждым пользователем
SELECT u.name, COUNT(bb.id) as books_borrowed
FROM users u
LEFT JOIN borrowed_books bb ON u.id = bb.user_id
GROUP BY u.id, u.name
ORDER BY books_borrowed DESC;

-- Обновление информации о пользователе
UPDATE users 
SET name = 'Иван Петров-Сидоров', registration_date = '2023-01-20'
WHERE id = 1;

-- Удаление данных о пользователе и всех связанных записей о выданных книгах
-- Сначала удаляем связанные записи в borrowed_books
DELETE FROM borrowed_books WHERE user_id = 3;

-- Затем удаляем пользователя
DELETE FROM users WHERE id = 3;

-- Дополнительные полезные запросы:

-- Показать все книги с авторами
SELECT b.title, a.name as author, b.publication_year, b.genre
FROM books b
JOIN authors a ON b.author_id = a.id
ORDER BY a.name, b.publication_year;

-- Показать историю выдачи книг
SELECT u.name as user, b.title as book, a.name as author, 
       bb.borrow_date, bb.return_date
FROM borrowed_books bb
JOIN users u ON bb.user_id = u.id
JOIN books b ON bb.book_id = b.id
JOIN authors a ON b.author_id = a.id
ORDER BY bb.borrow_date DESC;