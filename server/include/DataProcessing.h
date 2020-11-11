#pragma once

class DataProcessing {
public:
    DataProcessing() = default;

    template<class Data = int>
    static void SortOnTime(Data& data);

    struct Data {
        /// Данные по которым можно отсортировать по популярности
    };
    static void SortPopular(Data& data);
};