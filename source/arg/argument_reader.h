/**
 * \file
 * \brief
 *
 */

#ifndef _ARGUMENT_READER_H_
#define _ARGUMENT_READER_H_


#include <string>
#include <vector>
#include <iostream>
#include <set>

#include "argument.h"
#include "names.h"


namespace arg {


// Список хендлеров, которые определяются в main.cpp

void processArgument_help();
void processArgument_version();


class ArgumentReader
{

private:

    static const unsigned int _descriptionLineSize = 50;

    static std::vector<Argument*> _availableArguments;

public:

    ~ArgumentReader() {}

    static void read(int argc, char * argv[]);
    static Argument::Type defineType(const std::string & argument);

    static void printHelp();

};


} // namespace arg


#endif  // _ARGUMENT_READER_H_