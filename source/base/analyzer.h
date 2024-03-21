#ifndef _ANALYZER_H_
#define _ANALYZER_H_


#include <vector>
#include <iostream>
#include <sstream>

#include "names.h"
#include "fs.h"


namespace base {


class Analyzer
{

public:

    class Counters
    {

    public:

        unsigned int comments   = 0;
        unsigned int codes      = 0;
        unsigned int spaces     = 0;
        unsigned int all        = 0;

    public:

        Counters() {};
        ~Counters() {};

        Counters operator += (Counters & other)
        {
            this->comments += other.comments;
            this->codes += other.codes;
            this->spaces += other.spaces;
            this->all += other.all;

            return *this;
        }

    };

    Counters counters_global_cpp;
    Counters counters_global_h;

private:

    struct DirStat
    {
        std::vector<fs::path> dirs;
        std::vector<fs::path> files;
    };

    class FileInfo
    {

    public:

        fs::path path;
        Counters counters;

    public:

        FileInfo() {};
        ~FileInfo() {};

        std::string dump()
        {
            std::stringstream ss;
            ss << "\"" << path.filename().string() << "\" | Lines - " << counters.all << ": code - "
               << counters.codes << " , comm - " << counters.comments << " , sp - "
               << counters.spaces;
            return ss.str();
        }
    };

public:

    Analyzer();
    ~Analyzer();

    bool analyze(const std::string & path);

private:

    bool _dirStat(const std::string & path, DirStat & dirStat);

    bool _parseFile(FileInfo & file);

    void _simplifyLine(std::string & line);

};


} // namespace base


#endif // _ANALYZER_H_
