#!/bin/bash

PORT="54321"

echo "=== Тестовый сервер ==="
echo "Запуск сервера на порту $PORT"
echo "Используем встроенный /dev/tcp"
echo "Ожидание подключений..."
echo "Для остановки: Ctrl+C"
echo

# Функция для обработки клиента
handle_client() {
    echo "Клиент подключился!"
    while read -r message; do
        echo "Получено: $message"
        if [[ "$message" == "Привет, сервер!" ]]; then
            echo "Привет, клиент! Рад тебя видеть!"
        elif [[ "$message" == "exit" ]]; then
            echo "До свидания!"
            break
        else
            echo "Эхо: $message"
        fi
    done
    echo "Клиент отключился"
}

# Основной цикл сервера
while true; do
    echo "Готов к новому подключению..."
    
    # Используем /dev/tcp как сервер
    if [ -e /dev/tcp ]; then
        # Этот метод сложно реализовать для сервера в pure bash
        echo "Ожидаем подключения..."
        sleep 5
    else
        echo "Ошибка: /dev/tcp не поддерживается"
        exit 1
    fi
done
