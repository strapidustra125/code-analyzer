/**
 * \file
 * \brief
 *
 */


#include "argument_reader.h"

#include <iostream>
#include <sstream>

#include "names.h"
#include "version.h"


namespace arg {


std::vector<Argument*> ArgumentReader::_availableArguments =
{
    new Argument(
        Argument::help,
        "-h",
        "--help",

        "Выводит детальную информацию о приложении и доступных аргументах.",

        "Print detailed information about application and available arguments.",

        processArgument_help
    ),

    new Argument(
        Argument::version,
        "-v",
        "--version",

        "Выводит версию приложения и выходит.",

        "Return application version and exit.",

        processArgument_version
    )
};


void ArgumentReader::read(int argc, char * argv[])
{
    for(int i = 0; i < argc; i++)
    {
        auto argType = ArgumentReader::defineType(argv[i]);
        if(argType == Argument::Type::unknown) continue;

        for(auto availableArgument : _availableArguments)
            if(availableArgument->type == argType)
                availableArgument->process();
    }
}


Argument::Type ArgumentReader::defineType(const std::string & argument)
{
    for(auto availableArgument : _availableArguments)
        if(availableArgument->isMatchType(argument)) return availableArgument->type;

    return Argument::Type::unknown;
}


void ArgumentReader::printHelp()
{
    // Заголовок

    std::cout << std::endl;
    std::cout << "Project \"" << name::general::project << "\"" << std::endl;
    std::cout << std::endl;

    // Описание

    std::stringstream ss;
    ss << name::general::description;

    unsigned int curLineSize = 0;
    std::string word;
    while(ss >> word)
    {
        // std::cout << "word = [" << word << "]\n";
        if(curLineSize + word.size() > _descriptionLineSize)
        {
            std::cout << std::endl;
            curLineSize = 0;
        }

        std::cout << word << " ";
        curLineSize += word.size();
        // std::cout << "Length: " << curLineSize << "/" << _descriptionLineSize << "\n";
    }
    std::cout << std::endl << std::endl;

    // Аргументы

    std::cout << "Available arguments list:";
    std::cout << std::endl << std::endl;

    for(auto arg : _availableArguments) std::cout << arg->info();

    // Подпись

    std::cout << "Created by " << name::general::author << std::endl;
    std::cout << std::endl;
    std::cout << "Build on " << __DATE__ << " at " << __TIME__ << std::endl;
    std::cout << std::endl;
}


} // namespace arg
