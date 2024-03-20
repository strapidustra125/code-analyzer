/**
 * \file
 * \brief Версия приложения
 *
 * \details Значение, возвращаемое модулем при запуске с ключом "-v". Подробнее об изменениях в
 * каждой версии в файле changeLog.
 */

#ifndef _VERSION_H_
#define _VERSION_H_


#include <string>
#include <vector>


/**
 * \brief Константа с версией приложения в формате X1.X2
 * \details
 * - X1 - Вторая версия приложения
 * - X2 - Номер MVP
 */
const std::vector<int> partialVersion =
{
    1,  // Номер MVP
    2   // Номер коммита
};


/// Строковое значение версии приложения
inline std::string appVersion()
{
    std::string result;
    for(auto i = partialVersion.begin(); ; i++)
    {
        result += std::to_string(*i);
        if(i == partialVersion.end() - 1) break;
        result += ".";
    }
    return result;
}


#endif  // _VERSION_H_