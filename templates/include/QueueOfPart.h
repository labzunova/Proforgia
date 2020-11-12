//
// Created by nina on 11.11.2020.
//

#ifndef PROFORGIA_QUEUEOFPART_H
#define PROFORGIA_QUEUEOFPART_H

#include <string>
#include "Part.h"
#include "Context.h"

namespace templates{
    class QueueOfPart{ //очередь из созданных частей для объединения их в одну структуру
        bool IsEmpty() const;
        void render(templates::Context & context); //рендеринг каждой части
        std::string get_result() const;  //геттер результата
        void pop();                      //взять элемент из очереди
        void push(Part *ptr);            //добавление в очередь
    private:
        std::string result;
    };
}

#endif //PROFORGIA_QUEUEOFPART_H
