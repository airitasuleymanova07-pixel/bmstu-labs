#!/bin/bash

if [ $# -ne 1 ]; then
    echo "Ошибка: Необходимо передать имя файла в качестве аргумента"
    echo "Использование: $0 <имя_файла>"
    exit 1
fi

filename=$1

if [ ! -e "$filename" ]; then
    echo "Ошибка: Файл '$filename' не существует"
    exit 1
fi

if [ ! -f "$filename" ]; then
    echo "Ошибка: '$filename' не является обычным файлом"
    exit 1
fi

echo "=== Информация о файле: $filename ==="

echo "1. Информация через ls -l:"
ls -l "$filename"

echo

echo "2. Информация через stat:"
stat "$filename"

echo

echo "3. Детальная информация:"
echo "   - Размер файла: $(stat -c%s "$filename") байт"
echo "   - Дата последней модификации: $(stat -c%y "$filename")"
echo "   - Права доступа: $(stat -c%a "$filename") ($(stat -c%A "$filename"))"
echo "   - Владелец: $(stat -c%U "$filename")"
echo "   - Группа: $(stat -c%G "$filename")"
echo "   - Тип файла: $(stat -c%F "$filename")"
