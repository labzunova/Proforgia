#pragma once

#include <string>

template<class Key = std::string, class Value = std::string>
class Context {
public:
    class InterfacePresent {
    public:
        InterfacePresent() = default;
    };

    class ObjectView {
    };

public:
    Context() = default;

    void put(Key key, Value value);
    Value get(Key key);

    ObjectView GetView();
    void GenerationView(InterfacePresent* present);
};
