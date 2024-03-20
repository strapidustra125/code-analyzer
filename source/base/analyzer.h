#ifndef _ANALYZER_H_
#define _ANALYZER_H_


#include <vector>
#include <iostream>

#include "names.h"
#include "fs.h"


namespace base {


class Analyzer
{

public:

    struct Counters
    {
        unsigned int comments   = 0;
        unsigned int codes      = 0;
        unsigned int spaces     = 0;
        unsigned int all        = 0;

    } counters_global;

private:

    struct DirStat
    {
        std::vector<fs::path> dirs;
        std::vector<fs::path> files;
    };

public:

    Analyzer();
    ~Analyzer();

    bool analyze(const std::string & path);

private:

    bool _dirStat(const std::string & path, DirStat & dirStat);

    bool _parseFile(const std::string & path, Counters & counters);

    void _simplifyLine(std::string & line);

};


} // namespace base


#endif // _ANALYZER_H_
