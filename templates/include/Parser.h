//
// Created by nina on 10.11.2020.
//

#ifndef PROFORGIA_PARSER_H
#define PROFORGIA_PARSER_H

#include <string>
#include "Part.h"
#include "QueueOfPart.h"

namespace templates {
    class PartParser{ //главный абстрактный класс, от него будут наследоваться парсеры для разных частей
    public:
        virtual Part* parse() const = 0;
    protected:
        std::string::const_iterator start;
        std::string::const_iterator end;
    };

    class Parser{
    public:
        QueueOfPart parse(const std::string::const_iterator &begin, const std::string::const_iterator &end);
    private:
        PartParser *partParser;
    };
}

#endif //PROFORGIA_PARSER_H
