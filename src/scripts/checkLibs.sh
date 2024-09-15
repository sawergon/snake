#!/bin/bash
# Проверяем наличие установленного brew
if ! command -v brew &> /dev/null; then
   echo "Homebrew (brew) не установлен. Устанавливаем..."
#       /bin/bash -c "$(curl -fsSL https://raw.githubusercontent.com/Homebrew/install/HEAD/install.sh)"
   sh brewInstall.sh
fi
# Проверяем наличие библиотеки check
if brew list -1 | grep -q "check"; then
    echo "Библиотека check уже установлена."
else
    echo "Библиотека check не установлена. Устанавливаем..."
    # Устанавливаем библиотеку check
    brew install check
    brew install gcc
    brew install pkg-config
fi

# Проверяем наличие библиотеки ncurses
if brew list -1 | grep -q "ncurses"; then
    echo "Библиотека ncurses уже установлена."
else
    echo "Библиотека ncurses не установлена. Устанавливаем..."
    # Устанавливаем библиотеку ncurses
    brew install ncurses
fi

# Проверяем наличие библиотеки gtest
if brew list -1 | grep -q "gtest"; then
    echo "Библиотека gtest уже установлена."
else
    echo "Библиотека gtest не установлена. Устанавливаем..."
    # Устанавливаем библиотеку gtest и зависимости
    brew install gtest
    brew install gcc
    brew install pkg-config
fi