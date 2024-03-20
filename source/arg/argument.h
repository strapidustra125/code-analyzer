/**
 * \file
 * \brief
 *
 */

#ifndef _ARGUMENTS_H_
#define _ARGUMENTS_H_


#include <string>
#include <vector>
#include <functional>


namespace arg {


class Argument
{

public:

    enum Type
    {
        help,
        version,
        unknown
    }
    type = unknown;

private:

    static const unsigned int _descriptionLineSize = 50;
    bool _isRusInfoEnabled = true;

    const std::string _t        = "    ";
    const std::string _tab      = "|" + _t;
    const std::string _tab2     = "|" + _t + _t;
    const std::string _tab_d    = _tab2 + "     ";

    std::string _shortName;
    std::string _longName;

    std::string _description_rus;
    std::string _description_eng;

    std::function<void()> _handler;

public:

    Argument(
        const Type & type,
        const std::string & shortName,
        const std::string & longName,
        const std::string & description_rus,
        const std::string & description_eng,
        const std::function<void()> & handler
    );

    ~Argument();

    std::string info();
    bool isMatchType(const std::string & argumentName);
    void process();

};


} // namespace arg


#endif  // _ARGUMENTS_H_