CREATE DATABASE library;

\c library

CREATE TABLE authors (
    id SERIAL PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    birth_year INT
);

CREATE TABLE books (
    id SERIAL PRIMARY KEY,
    title VARCHAR(200) NOT NULL,
    author_id INT REFERENCES authors(id),
    publication_year INT,
    genre VARCHAR(50)
);

CREATE TABLE users (
    id SERIAL PRIMARY KEY,
    name VARCHAR(100) NOT NULL,
    registration_date DATE DEFAULT CURRENT_DATE
);

CREATE TABLE borrowed_books (
    user_id INT REFERENCES users(id),
    book_id INT REFERENCES books(id),
    borrow_date DATE DEFAULT CURRENT_DATE,
    return_date DATE,
    PRIMARY KEY(user_id, book_id, borrow_date)
);

CREATE INDEX idx_authors_name ON authors(name);
CREATE INDEX idx_books_title ON books(title);
CREATE INDEX idx_borrowed_books_date ON borrowed_books(borrow_date);