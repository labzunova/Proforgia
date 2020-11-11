#pragma once

#include "string"

class GeneratorKey {
public:
    GeneratorKey() = delete;

    static GeneratorKey& GetInstance();
    void HashPassword(std::basic_string<char> password );
    std::string GetKey();
    std::string GetSession();
};
