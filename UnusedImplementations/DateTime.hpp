#ifndef DATETIME_HPP
#define DATETIME_HPP
#include <string>

class DateTime
{
    private:
        std :: string date;
        std :: string day;
        std :: string time;

    public:
        DateTime();
        std :: string displayDate(std :: string format);
};

#endif