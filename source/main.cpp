/**
 * \file
 * \brief
 */


#include <string>
#include <iostream>

#include "argument_reader.h"
#include "fs.h"
#include "version.h"
#include "analyzer.h"


// ---------------------------------------------------------------------------------------------- //
// Реализации методов обработки входных аргументов приложения

void arg::processArgument_help()
{
    arg::ArgumentReader::printHelp();
    exit(0);
}

void arg::processArgument_version()
{
    std::cout << appVersion() << std::endl;
    exit(0);
}


// ---------------------------------------------------------------------------------------------- //


/// Точка входа в приложение
int main(int argc, char * argv[])
{
    arg::ArgumentReader::read(argc, argv);

    if(argc != 2)
    {
        std::cerr << "Please, give counting directory as a parameter" << std::endl;
        return -1;
    }

    base::Analyzer analyzer;

    return analyzer.analyze(argv[1]);
}
