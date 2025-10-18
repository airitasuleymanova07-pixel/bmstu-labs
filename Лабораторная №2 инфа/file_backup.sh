#!/bin/bash 

if [ -f "important.txt" ]; then 
	cp important.txt important_backup. 
txt
	echo "Резервная копия создана: important_backup.txt" 
else 
	echo "Файл important.txt не найден"
fi 
