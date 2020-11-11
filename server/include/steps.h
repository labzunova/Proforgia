#pragma once

#include "Context.h"
#include <string>

typedef Context<std::string, std::string> ContextStr;
class Step {
public:
    enum Status {
        OK,
        FAILED,
        SYS_FAILED,
    };

public:
    virtual ~Step() = default;
    Step() : next_(nullptr) {};

    void SetNext(Step* step);
    virtual Status Run(ContextStr& context) = 0;

protected:
    Status Next(ContextStr& context);
    Step* next_;
};


class Hash : public Step {
    Status Run(ContextStr& context) override;
};

class CheckLogin : public Step {
    Status Run(ContextStr& context) override;
};

class GenSession : public Step {
    Status Run(ContextStr& context) override;
};

class SessionSave : public Step {
    Status Run(ContextStr& context) override;
};

class CheckUser : public Step {
    Status Run(ContextStr& context) override;
};

class RoomPrep : public Step {
    Status Run(ContextStr& context) override;
};

class RoomSave : public Step {
    Status Run(ContextStr& context) override;
};

class UserUpdate : public Step {
    Status Run(ContextStr& context) override;
};

class GetRoom : public Step {
    Status Run(ContextStr& context) override;
};

class GetUser : public Step {
    Status Run(ContextStr& context) override;
};

class CreateView : public Step {
    Status Run(ContextStr& context) override;
};

class DataSave : public Step {
    Status Run(ContextStr& context) override;
};

class DataDelete : public Step {
    Status Run(ContextStr& context) override;
};

class GetData : public Step {
    Status Run(ContextStr& context) override;
};

class Deadline : public Step {
    Status Run(ContextStr& context) override;
};

class SortPopularData : public Step {
    Status Run(ContextStr& context) override;
};
