#!/bin/bash

makefile_dir=""
arguments=("$@")

libs_dir_path=${arguments[0]}
unset 'arguments[0]'
# Проверка существования директории libs_dir_path
if [ ! -d "$libs_dir_path" ]; then
    echo "Ошибка: Директория $libs_dir_path не найдена."
    exit 1
fi

cd $libs_dir_path || exit

for ((i=1; i<$#; i+=1))
do
    makefile_dir=${arguments[i]}

    # Проверяем существование Makefile
    if [ -f "$makefile_dir/Makefile" ]; then
        (cd $makefile_dir && make clean)
        make_exit_code=$?
        if [ $make_exit_code -ne 0 ]; then
            echo "Предупреждение: make завершился с кодом возврата $make_exit_code"
        fi
    else
        echo "Makefile не найден в директории $makefile_dir"
    fi
done