//
// Created by nina on 10.11.2020.
//

#ifndef PROFORGIA_LOADER_H
#define PROFORGIA_LOADER_H

#include <string>
#include "Parser.h"

namespace templates {
    class Loader {
    public:
        explicit Loader(const std::string &path); //view дает пути
        void loadFile(const std::string &filename); //оисходит загрузка данного файла
        std::string get_result() const;
    private:
        std::string templatesPath; //переменные для хранения путей(возможно использованеи  boost::filesystem::path )
        std::string includesPath;
        std::string result; //хранение результата в виде строки
        Parser parser;
    };
}

#endif //PROFORGIA_LOADER_H
