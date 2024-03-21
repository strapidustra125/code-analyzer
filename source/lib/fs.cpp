/**
 * \file
 * \brief Реализация методов класса FS для базовых операция с файловой системой.
 * \details Больше информации в описании класса FS.
 */

#include "fs.h"

#include "names.h"

#include <fstream>
#include <stdio.h>
#include <iostream>


/**
 * \brief Возвращает строку типа std::string с абсолютным путем до рабочей директории
 * \details Использует функцию current_path библиотеки <filesystem>
 * \return Строку типа std::string с абсолютным путем до рабочей директории.
 */
std::string FS::currentDir()
{
    return fs::current_path().string();
}


/* ------------------------------- Методы для работы с файлами ------------------------------ */

/**
 * \brief Проверка наличия файла по заданному абсолютному пути.
 * \details Использует функции exists и is_regular_file библиотеки <filesystem>.
 * \param [in] path - Константная ссылка на абсолютный путь типа std::string до файла.
 * \return
 * - true - файл существует.
 * - false - файл не существует.
 */
bool FS::File::isExists(const std::string & path)
{
    if(path.empty()) return false;

    std::error_code err;
    fs::path filePath = path.c_str();

    if(fs::exists(filePath, err) && fs::is_regular_file(filePath, err)) return true;
    else return false;
}

/**
 * \brief Чтение файла целиком в бинарном режиме
 * \details Читает файл в строку целиком в бинарном режиме при помощи последовательного вызова
 * функции std::getline.
 * \param [in] path - Константная ссылка на строковую переменную пути до читаемого файла
 * \param [out] data - Ссылка на строку с результатом чтения файла
 * \return
 * - true - Успешная запись
 * - false - Ошибка при записи
 */
bool FS::File::read(const std::string & path, std::string & data)
{
    if(!File::isExists(path))
    {
        std::cerr << "Unable to read file [" << path << "]: file does not exist!" << std::endl;
        return false;
    }

    std::ifstream file(path, std::ios::in | std::ios::binary);

    if(!file.is_open())
    {
        std::cerr << "Unable to read file [" << path << "]: file was not opened" << std::endl;
        return false;
    }

    data = "";
    std::string allData     = "";
    std::string currentData = "";

    while(!file.eof())
    {
        std::getline(file, currentData);
        allData += currentData;
        if (!file.eof()) allData += '\n';
    }

    file.close();

    data = allData;
    return true;
}


/* ---------------------------- Методы для работы с директориями ---------------------------- */

/**
 * \brief Проверка наличия директории по заданному абсолютному пути.
 * \details Использует функции exists и is_directory библиотеки <filesystem>.
 * \param [in] path - Константная ссылка на абсолютный путь типа std::string до директории.
 * \return
 * - true - файл существует.
 * - false - файл не существует.
 */
bool FS::Dir::isExists(const std::string & path)
{
    if(path.empty()) return false;

    std::error_code err;
    fs::path filePath = path.c_str();

    if(fs::exists(filePath, err) && fs::is_directory(filePath, err)) return true;
    else return false;
}

/**
 * \brief Получить список файлов директории в вектор
 * \details Проверяет путь path, существующая ли это директория. С помощью directory_entry
 * перебирает содержимое: если это файл и его имя содержит filter, то добавляет в вектор его
 * путь.
 * \param [in] path - Константная ссылка на абсолютный путь типа std::string до директории.
 * \param [out] files - Ссылка на вектор путей файлов, содержащихся в директории.
 * \param [in] filter - Константная ссылка на строку фильтра для поиска файлов.
 * \return
 * - true - Успешное получение содержимого
 * - false - Ошибка
 */
bool FS::Dir::getFilesPaths(const std::string & path, std::vector<fs::path> & filePaths, const std::string & filter)
{
    if(path.empty())
    {
        std::cerr << "Unable to get files paths in dir [" << path << "]: path is empty!" << std::endl;
        return false;
    }

    std::error_code err;
    fs::path dirPath = path.c_str();

    if(!fs::exists(dirPath, err) || !fs::is_directory(dirPath, err))
    {
        std::cerr << "Unable to get files paths in dir [" << path << "]: path NOT exist or NOT a directory." << std::endl;
        return false;
    }

    filePaths.clear();

    for(const fs::directory_entry &entry : fs::directory_iterator{dirPath})
    {
        if (!fs::is_regular_file(entry.path(), err)) continue;

        fs::path filePath = entry.path().string();
        std::string name = filePath.filename().string();

        if(filter.size() > name.size())
        {
            std::cerr << "File [" << name << "] less then extension [" << filter << "]" << std::endl;
            return false;
        }

        bool found = true;
        int j = name.size() - 1;
        for(int i = filter.size() - 1; i >= 0; i--)
        {
            if(name[j--] != filter[i])
            {
                found = false;
                break;
            }
        }

        if(found) filePaths.push_back(filePath);
    }

    return true;
}


bool FS::Dir::getDirsPaths(const std::string & path, std::vector<fs::path> & dirs)
{
        if(path.empty())
    {
        std::cerr << "Unable to get files paths in dir [" << path << "]: path is empty!" << std::endl;
        return false;
    }

    std::error_code err;
    fs::path dirPath = path.c_str();

    if(!fs::exists(dirPath, err) || !fs::is_directory(dirPath, err))
    {
        std::cerr << "Unable to get files paths in dir [" << path << "]: path NOT exist or NOT a directory." << std::endl;
        return false;
    }

    dirs.clear();

    for(const fs::directory_entry &entry : fs::directory_iterator{dirPath})
    {
        if (!fs::is_directory(entry.path(), err)) continue;

        fs::path dirPath = entry.path().string();
        dirs.push_back(dirPath);
    }

    return true;
}
