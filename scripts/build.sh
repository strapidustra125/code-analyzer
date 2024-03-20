#!/bin/bash

# Переменные
PROJECT="code-analyzer"


# Лог в случае ошибки с выходом из скрипта
function LOG_ERR {
    echo -e "\nERROR: $1\n"
    echo -e "ERROR: Build \"${PROJECT}\" project failed :("
    exit -1
}

# Штатный лог
function LOG {
    echo -e "\n$1\n"
}


LOG "Building ${PROJECT}..."

# Удаляем весь мусор из build и release
cd ..
rm -rf build
rm -rf release

# Создаем ее чистенькую и переходим туда
mkdir build
cd build


# ================================ Подготовка к сборке проекта =============================== #

LOG "Starting \"cmake\" for \"${PROJECT}\" project:"

# Запуск утилиты CMAKE
# .. - директория, в которой лежит CMakeLists.txt
cmake  ..

rc=$?
if [ ${rc} != 0 ]
then
    LOG_ERR "cmake failed: rc = ${rc}"
fi

LOG "\"cmake\" for \"${PROJECT}\" project finished!"


# =============================== Сборка проекта с помощью make ============================== #

LOG "Starting \"make\" for \"${PROJECT}\" project:"

# Запуск утилиты make на nproc ядрах процессора (на всех)
# make собирает бинарник модуля из исходников

# VERBOSE=1
make -j$(nproc)

rc=$?
if [ ${rc} != 0 ]
then
    LOG_ERR "make failed: rc = ${rc}"
fi

LOG "\"make\" for \"${PROJECT}\" project finished!"


# Вывод информации о собранном файле. Если будет ошибка - значит файл не собрался.
RESULT=../release/${PROJECT}

# Проверка наличия бинарника и вывод строки со статусом сборки
if [ ! -f ${RESULT} ]
then
    LOG_ERR "No file"
fi

echo -n "Result file info: "
file ${RESULT}
LOG "\"${PROJECT}\" was successfully builded!"
exit 0