#include "analyzer.h"

#include "fs.h"


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

    DirStat dirStat;
    _dirStat(path, dirStat);

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



} // namespace base
