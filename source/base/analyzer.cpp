#include "analyzer.h"

#include "fs.h"

#include <fstream>


namespace base {


Analyzer::Analyzer()
{

}


Analyzer::~Analyzer()
{

}


bool Analyzer::analyze(const std::string & path)
{
    if(!FS::Dir::isExists(path))
    {
        std::cerr << "Unable to find directory [" << path << "]" << std::endl;
        return false;
    }

    Counters counters;
    _parseFile(path + "/" + "main.cpp", counters);

    DirStat dirStat;
    // _dirStat(path, dirStat);

    return true;
}



// ---------------------------------------------------------------------------------------------- //

bool Analyzer::_dirStat(const std::string & path, DirStat & dirStat)
{
    static std::string tab = "";
    tab += "    ";

    std::vector<fs::path> dirs;
    if(!FS::Dir::getDirsPaths(path, dirs)) return false;

    std::vector<fs::path> files_cpp;
    if(!FS::Dir::getFilesPaths(path, files_cpp, ".cpp")) return false;

    std::vector<fs::path> files_hpp;
    if(!FS::Dir::getFilesPaths(path, files_hpp, ".hpp")) return false;

    std::vector<fs::path> files_c;
    if(!FS::Dir::getFilesPaths(path, files_c, ".c")) return false;

    std::vector<fs::path> files_h;
    if(!FS::Dir::getFilesPaths(path, files_h, ".h")) return false;

    int fileAmount = files_cpp.size() + files_hpp.size() + files_c.size() + files_h.size();


    for(auto dir : dirs)
    {
        std::cout << tab << dir.filename().string() << "/" << std::endl;
        _dirStat(path + "/" + dir.filename().string(), dirStat);
        tab = tab.substr(0, tab.size() - 4);
    }

    for(auto file : files_cpp)  std::cout << tab << "-> " << file.filename().string() << std::endl;
    for(auto file : files_hpp)  std::cout << tab << "-> " << file.filename().string() << std::endl;
    for(auto file : files_c)    std::cout << tab << "-> " << file.filename().string() << std::endl;
    for(auto file : files_h)    std::cout << tab << "-> " << file.filename().string() << std::endl;

    return true;
}

bool Analyzer::_parseFile(const std::string & path, Counters & counters)
{
    if(!FS::File::isExists(path))
    {
        std::cerr << "Unable to find file [" << path << "]" << std::endl;
        return false;
    }

    std::ifstream file(path, std::ios::in | std::ios::binary);

    if(!file.is_open())
    {
        std::cerr << "Unable to read file [" << path << "]: file was not opened" << std::endl;
        return false;
    }

    bool longComment = false;
    while(!file.eof())
    {
        std::cout << "--------------------------" << std::endl;

        counters.all++;

        std::string line = "";
        std::getline(file, line);

        std::cout << "[" << line << "]" << std::endl;

        _simplifyLine(line);

        if(line[0] == '/' && line[1] == '*') longComment = true;
        if(line[line.size() - 1] == '*' && line[line.size() - 2] == '/') longComment = true;

        if(line == "")
        {
            counters.spaces++;
            std::cout << " | spaces" << std::endl;
        }
        else if(line[0] == '/' && line[1] == '/')
        {
            counters.comments++;
            std::cout << " | comments" << std::endl;
        }
        else 
        {
            counters.codes++;
            std::cout << " | codes" << std::endl;
        }
    }

    file.close();

    std::cout << "all: "        << counters.all << std::endl;
    std::cout << "spaces: "     << counters.spaces << std::endl;
    std::cout << "comments: "   << counters.comments << std::endl;
    std::cout << "codes: "      << counters.codes << std::endl;
}

/// Отрезает от строки незначащие пробелы и табуляции
void Analyzer::_simplifyLine(std::string & line)
{
    if(line == "") return;

    std::cout << "1:" << "[" << line << "]" << std::endl;

    // Откусить пробелы и табы в начале
    for(int i = 0; i < line.size(); i++)
    {
        if(line[i] != ' ' && line[i] != '\t')
        {
            line.substr(i, line.size());
            std::cout << "sub: " << i << " - " << line.size() << std::endl;
            break;
        }
    }

    std::cout << "2:" << "[" << line << "]" << std::endl;

    // Откусить пробелы и табы в конце
    for(int i = line.size() - 1; i <= 0; i--)
    {
        if(line[i] != ' ' && line[i] != '\t')
        {
            line.substr(0, i);
            std::cout << "sub: " << 0 << " - " << i << std::endl;
            std::cout << "3:" << "[" << line << "]" << std::endl;
            return;
        }
    }

    line = "";
}


} // namespace base
