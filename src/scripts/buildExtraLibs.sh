#!/bin/bash

if [ "$(($# % 2))" -eq 0 ]; then
    echo "Ошибка: Четное количество входных аргументов. Пожалуйста, введите четное количество строк."
    exit 1
fi

makefile_dir=""
build_libs_target=""
arguments=("$@")

libs_dir_path=${arguments[0]}
unset 'arguments[0]'
# Проверка существования директории libs_dir_path
if [ ! -d "$libs_dir_path" ]; then
    echo "Ошибка: Директория $libs_dir_path не найдена."
    exit 1
fi

cd $libs_dir_path || exit

for ((i=1; i<$#; i+=2))
do
    makefile_dir=${arguments[i]}
    build_libs_target=${arguments[i+1]}

    # Проверяем существование Makefile
    if [ -f "$makefile_dir/Makefile" ]; then
        echo "Вызываем цель $build_libs_target в Makefile в директории $makefile_dir"
        (cd $makefile_dir && make $build_libs_target)
        make_exit_code=$?
        if [ $make_exit_code -ne 0 ]; then
            echo "Предупреждение: make завершился с кодом возврата $make_exit_code"
        else
          (cd $makefile_dir && mv $build_libs_target ../../)
        fi
    else
        echo "Makefile не найден в директории $makefile_dir"
    fi
done