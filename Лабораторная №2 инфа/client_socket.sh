#!/bin/bash

PORT="54321"

echo "=== Простой сервер ==="
echo "Порт: $PORT"
echo "Ожидание подключения..."

# Используем /dev/tcp для сервера
while true; do
    # Слушаем порт и обрабатываем подключение
    {
        echo "Клиент подключился!"
        while read -r message; do
            echo "Получено: $message"
            if [[ "$message" == "Привет, сервер!" ]]; then
                echo "Привет, клиент!"
            elif [[ "$message" == "exit" ]]; then
                echo "Пока!"
                break
            else
                echo "Эхо: $message"
            fi
        done
        echo "Клиент отключился"
    } | nc -l -p $PORT 2>/dev/null || {
        echo "Ошибка: не могу запустить сервер"
        echo "Проверьте доступность netcat или используйте другой метод"
        exit 1
    }
done
