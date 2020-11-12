//
// Created by nina on 10.11.2020.
//
#ifndef PROFORGIA_CONTEXT_H
#define PROFORGIA_CONTEXT_H
#include <string>
#include <map>


namespace templates { //все классы, рабтающие с шаблонами будут относиться к данному пространству имен
    class Context{    //класс, осуществляющий взаимодействие с response и request, хранит все данные полученные от сервера, чтоб вставлять во время рендеринга
    public:
        Context() = default;
        explicit Context(const std::string &json); //получение нашего json в качестве просто строки
        std::string fromPtreeToStr() const; //созданеи из boost::property_tree::ptree просто строку json
        std::map<std::string, std::string> fromPrteeToMap(); //для создания мапы(поддерживает одинаковые ключи)
        template<class T>
        void put(const std::string &name, const T &value); //методы положить и взять в root данные по ключу
        template<class T>
        T get(const std::string &name) const;
    private:
       std::map<std::string, std::string> root; //удобная древовидна структура отображения данных(библиотека имеет встроенный парсер)(возможна реализация с помощью типа  boost::property_tree::ptree )

    };

}
#endif //PROFORGIA_CONTEXT_H

/*сеть дергает сервер и на сервере данные полученные из бд в класс заполняют поля контекста, эти данные подаются на рендеринг странички, имя которой установил сервер,
 * в процессе рендеринга мы через класс load загружаем наш файл подгружая зависимости ввиде включенных и унаследованных шаблонов, получив файл в текстовом формате и заэммапив его
 * мы отправляем непосредственно на рендеринг частей, формируются части, куда вставляются нужные данные, потом они соединяются в очередь и мы получаем готовую отрендеренную
 * страничку, которую возвращаем серверу, а оттуда его уже берет сеть в респонс*/