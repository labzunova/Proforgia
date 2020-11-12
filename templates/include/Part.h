//
// Created by nina on 11.11.2020.
//

#ifndef PROFORGIA_PART_H
#define PROFORGIA_PART_H

#include <string>
#include "Context.h"

namespace templates {
    class Part{  //главный абстрактный класс, от него будут наследоваться разные части и переопределять метод рендеринга
        virtual std::string render(templates::Context &context) = 0; //рендеринг части
        std::string get_content() const { return content; } //геттер для созданных готовых частей страницы
        std::string get_name() const { return name; }
        short int get_type() const { return type; }
    protected:
        std::string content;
        std::string name;
        short int type;
    };
}

#endif //PROFORGIA_PART_H
