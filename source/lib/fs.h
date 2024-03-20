/**
 * \file
 * \brief Описание класса FS для базовых операция с файловой системой.
 * \details Больше информации в описании класса FS.
 */


#ifndef _FS_HELPER_H_
#define _FS_HELPER_H_


#include <string>
#include <vector>
#include <mutex>

#include "names.h"

#include <experimental/filesystem>


/// Макрос для получения полного пути до текущей директории
#define CUR_DIR FS::currentDir() + "/"


namespace fs = std::experimental::filesystem;


/**
 * \file
 * \brief Статический класс для работы с файловой системой
 *
 * \details
 * Функции работы с файлами при помощи библиотеки <experimental/filesystem>.
 *
 * \warning
 * - Все функции принимают абсолютный путь до файла. Т.е. по умолчанию файл ищется в корне "/".
 *
 * \todo Добавить логирование внутрь всех хелперов
 * \todo Попробовать __builtin_FUNCTION()
 */
class FS
{

public:

    FS() = delete;
    ~FS() = delete;

    static std::string currentDir();

    struct File
    {
        static bool isExists(const std::string & path);

        static bool read(const std::string & path, std::string & data);
    };

    struct Dir
    {
        static bool isExists(const std::string & path);

        static bool getFilesPaths(const std::string & path, std::vector<fs::path> & files, const std::string & filter);
        static bool getDirsPaths(const std::string & path, std::vector<fs::path> & dirs);
    };
};


#endif // _FS_HELPER_H_
