#include "analyzer.h"

#include "fs.h"

#include <fstream>


namespace base {


Analyzer::Analyzer() {}

Analyzer::~Analyzer() {}


bool Analyzer::analyze(const std::string & path)
{
    if(!FS::Dir::isExists(path))
    {
        std::cerr << "Unable to find directory [" << path << "]" << std::endl;
        return false;
    }

    std::cout << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << std::endl;

    std::cout << "\"" << path << "\" statistics:" << std::endl;

    DirStat dirStat;
    _dirStat(path, dirStat);

    std::cout << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << std::endl;

    std::cout << "Total .c/.cpp stat. Lines : " << counters_global_cpp.all << std::endl
              << "    code     - " << counters_global_cpp.codes << std::endl
              << "    comments - " << counters_global_cpp.comments << std::endl
              << "    space    - " << counters_global_cpp.spaces << std::endl;

    std::cout << "Total .h/.hpp stat. Lines : " << counters_global_h.all << std::endl
              << "    code     - " << counters_global_h.codes << std::endl
              << "    comments - " << counters_global_h.comments << std::endl
              << "    space    - " << counters_global_h.spaces << std::endl;

    std::cout << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << std::endl;

    std::cout << "Total statistics. Lines : " << counters_global_h.all + counters_global_cpp.all << std::endl
              << "    code     - " << counters_global_h.codes + counters_global_cpp.codes << std::endl
              << "    comments - " << counters_global_h.comments + counters_global_cpp.comments << std::endl
              << "    space    - " << counters_global_h.spaces + counters_global_cpp.spaces << std::endl;

    std::cout << std::endl;
    std::cout << "---------------------------------------------" << std::endl;
    std::cout << std::endl;

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

    for(auto file : files_cpp)
    {
        FileInfo info;
        info.path = file;
        if(!_parseFile(info)) return false;
        std::cout << tab << "-> " << info.dump() << std::endl;
        counters_global_cpp += info.counters;
    }

    for(auto file : files_hpp)
    {
        FileInfo info;
        info.path = file;
        if(!_parseFile(info)) return false;
        std::cout << tab << "-> " << info.dump() << std::endl;
        counters_global_h += info.counters;
    }

    for(auto file : files_c)
    {
        FileInfo info;
        info.path = file;
        if(!_parseFile(info)) return false;
        std::cout << tab << "-> " << info.dump() << std::endl;
        counters_global_cpp += info.counters;
    }

    for(auto file : files_h)
    {
        FileInfo info;
        info.path = file;
        if(!_parseFile(info)) return false;
        std::cout << tab << "-> " << info.dump() << std::endl;
        counters_global_h += info.counters;
    }

    return true;
}

/// Подсчет строк файла: комментарии, строки кода и пустые строки
bool Analyzer::_parseFile(FileInfo & file)
{
    if(!FS::File::isExists(file.path))
    {
        std::cerr << "Unable to find file [" << file.path << "]" << std::endl;
        return false;
    }

    std::ifstream fin(file.path, std::ios::in | std::ios::binary);

    if(!fin.is_open())
    {
        std::cerr << "Unable to read file [" << file.path << "]: file was not opened" << std::endl;
        return false;
    }

    bool longComment = false;
    while(!fin.eof())
    {

        file.counters.all++;

        std::string line = "";
        std::getline(fin, line);

        _simplifyLine(line);

        if(line[0] == '/' && line[1] == '*') longComment = true;

        if(line[line.size() - 2] == '*' && line[line.size() - 1] == '/')
        {
            longComment = false;
            file.counters.comments++;
            continue;
        }

        if(longComment)
        {
            file.counters.comments++;
            continue;
        }

        if(line == "") file.counters.spaces++;
        else if(line[0] == '/' && line[1] == '/') file.counters.comments++;
        else file.counters.codes++;
    }

    fin.close();
    return true;
}

/// Отрезает от строки незначащие пробелы и табуляции
void Analyzer::_simplifyLine(std::string & line)
{
    if(line == "") return;

    // Откусить пробелы и табы в начале

    if(line[0] == ' ')
        for(unsigned int i = 0; i < line.size(); i++)
        {
            if(line[i] != ' ' && line[i] != '\t')
            {
                line = line.substr(i, line.size());
                break;
            }
        }

    // Откусить пробелы и табы в конце

    if(line[line.size() - 1] == ' ')
        for(int i = line.size() - 1; i >= 0; i--)
        {
            if(line[i] != ' ' && line[i] != '\t')
            {
                line = line.substr(0, i + 1);
                break;
            }
        }

    if(line[line.size() - 1] == ' ' || line[0] == ' ') line = "";
}


} // namespace base
