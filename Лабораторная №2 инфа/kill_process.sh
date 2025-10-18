#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Ошибка: Необходимо передать имя процесса в качестве аргумента"
    echo "Использование: $0 <имя_процесса>"
    exit 1
fi

process_name=$1

# Проверка, запущен ли процесс
if pgrep "$process_name" > /dev/null; then
    echo "Процесс '$process_name' найден. Завершение..."
    
    if pkill "$process_name"; then
        echo "Процесс '$process_name' успешно завершен"
    else
        echo "Ошибка: Не удалось завершить процесс '$process_name'"
        exit 1
    fi
else
    echo "Процесс '$process_name' не запущен"
    exit 1
fi
