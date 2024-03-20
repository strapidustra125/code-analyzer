/**
 * \file
 * \brief
 *
 */

#include "argument.h"


#include <string>
#include <iostream>
#include <vector>
#include <sstream>


namespace arg {


Argument::Argument( const Type &                    type,
                    const std::string &             shortName,
                    const std::string &             longName,
                    const std::string &             description_rus,
                    const std::string &             description_eng,
                    const std::function<void()> &   handler)
{
    this->type              = type;
    this->_shortName        = shortName;
    this->_longName         = longName;
    this->_description_rus  = description_rus;
    this->_description_eng  = description_eng;
    this->_handler          = handler;
}


Argument::~Argument() {}


std::string Argument::info()
{
    std::stringstream ss_result;

    if(type == unknown)
    {
        ss_result << _tab << "Unknown argument" << std::endl << std::endl;
        return ss_result.str();
    }

    // Команда вызова

    ss_result << _tab << _shortName << ", " << _longName << std::endl << _tab;

    std::stringstream ss_description;
    int curLineSize = 0;
    std::string word;

    // Описание на русском

    if(_isRusInfoEnabled && _description_rus.size() != 0)
    {
        ss_description << _description_rus;

        ss_result << std::endl << _tab2 << "RUS: ";

        while(ss_description >> word)
        {
            // Умножаем на 2, потому что кириллический символ занимает 2 байта
            if(curLineSize + word.size() > _descriptionLineSize * 2)
            {
                ss_result << std::endl << _tab_d;
                curLineSize = 0;
            }

            ss_result << word << " ";
            curLineSize += word.size();
        }

        ss_result << std::endl << _tab;
    }

    // Описание на английском

    ss_description.clear();
    curLineSize = 0;

    if(_description_eng.size() != 0)
    {
        ss_description << _description_eng;

        ss_result << std::endl << _tab2 << "ENG: ";

        while(ss_description >> word)
        {
            if(curLineSize + word.size() > _descriptionLineSize)
            {
                ss_result << std::endl << _tab_d;
                curLineSize = 0;
            }

            ss_result << word << " ";
            curLineSize += word.size();
        }
    }

    ss_result << std::endl << std::endl;

    return ss_result.str();
}


bool Argument::isMatchType(const std::string & argumentName)
{
    if(argumentName == _shortName || argumentName == _longName) return true;
    else return false;
}


void Argument::process()
{
    _handler();
}


} // namespace arg
