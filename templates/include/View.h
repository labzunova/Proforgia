//
// Created by nina on 10.11.2020.
//

#ifndef PROFORGIA_VIEW_H
#define PROFORGIA_VIEW_H
#include <string>
#include "Context.h"
#include "Loader.h"

namespace templates {
    class View{       //агрегирует в себе рендеринг странички(это вызовет сервер, передав контекст), в свою очередь загрузит сраничку и распарсит то, что надо
    public:
        explicit View(const std::string &path) : loader(path) {}; //в конструкторе мы устанавливаем путь(да его лоадеру)
        std::string render(templates::Context &context); //происходит заполнение контекста разными данными и он отдается на рендеринг в страничку,имя через set, вызывает сервис
        void setFileName(const std::string &filename);  //установление имени html файла
    private:
        Loader loader;
        Parser parser;
    };
}

#endif //PROFORGIA_VIEW_H
/*если сть должна забирать готовую страничку от меня, то ответ возвращает функция рендеринга и
 * если сеть передает мне прост разные классы, то я у себя принимаю перевожу в удобные данные*/