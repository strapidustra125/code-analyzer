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

    } counters;

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

};


} // namespace base


#endif // _ANALYZER_H_
