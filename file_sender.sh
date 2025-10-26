#!/bin/bash

if [ $# -ne 2 ]; then
    echo "Использование: $0 <директория> <порт>"
    echo "Пример: $0 my_files 8080"
    exit 1
fi

DIRECTORY="$1"
PORT="$2"
REMOTE_SERVER="localhost"  # Заменяем на адрес вашего сервера

# Создание директории, если его не существует
if [ ! -d "$DIRECTORY" ]; then
    echo "Директория $DIRECTORY не существует. Создаю..."
    mkdir -p "$DIRECTORY"
    if [ $? -ne 0 ]; then
        echo "Ошибка: Не удалось создать директорию $DIRECTORY"
        exit 1
    fi
    echo "Директория $DIRECTORY создана успешно."
else
    echo "Директория $DIRECTORY уже существует."
fi

# Создание 5 текстовых файлов
echo "Создаю файлы в директории $DIRECTORY..."
for i in {1..5}; do
    FILENAME="$DIRECTORY/file${i}.txt"
    echo "Создаю файл: $FILENAME"
    echo "Файл номер $i" > "$FILENAME"
    
    # Проверка успешности создания файла
    if [ $? -eq 0 ]; then
        echo "Файл $FILENAME создан успешно."
    else
        echo "Ошибка при создании файла $FILENAME"
        exit 1
    fi
done

echo "Все файлы созданы успешно."

# Отправка файлов через netcat
echo "Отправляю файлы на сервер $REMOTE_SERVER порт $PORT..."

# Проверяем доступность netcat
if ! command -v nc &> /dev/null; then
    echo "Ошибка: netcat не установлен. Установите его для продолжения."
    echo "Для Ubuntu/Debian: sudo apt-get install netcat"
    echo "Для CentOS/RHEL: sudo yum install nc"
    exit 1
fi

# Создаем tar архив и отправляем через netcat
tar -czf - "$DIRECTORY" | nc "$REMOTE_SERVER" "$PORT"

# Проверяем статус завершения netcat
NC_EXIT_CODE=$?
if [ $NC_EXIT_CODE -eq 0 ]; then
    echo "Файлы успешно отправлены на сервер."
else
    echo "Ошибка при отправке файлов."
    exit 1
fi

echo "Скрипт завершил работу успешно."