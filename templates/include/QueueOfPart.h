//
// Created by nina on 11.11.2020.
//

#ifndef PROFORGIA_QUEUEOFPART_H
#define PROFORGIA_QUEUEOFPART_H

#include <string>
#include "Part.h"
#include "Context.h"

namespace templates{
    class QueueOfPart{
        bool IsEmpty() const;
        void render(templates::Context & context);
        std::string get_result() const;
        void pop();
        void push(Part *ptr);
    private:
        std::string result;
    };
}

#endif //PROFORGIA_QUEUEOFPART_H
