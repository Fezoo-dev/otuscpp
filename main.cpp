#include <type_traits>
#include <iostream>
#include <list>
#include <vector>
#include <tuple>

/** 
 * Функция вывода `условного` ip-адреса в поток stream.
 * Адрес может быть представлен в виде произвольного целочисленного типа.
 * Выводится побайтово, начиная со старшего байта, с символом `.`(точка) в качестве разделителя.
 * */
template <typename T,
    typename Integral = typename std::enable_if_t<
        std::is_integral_v<T> and !std::is_floating_point_v<T>
        >
>
// Целочисленные типы можно передавать по значению.
void print_ip(std::ostream& stream, T ip){
    constexpr auto TYPE_SIZE = sizeof(T);
    constexpr auto BYTE_MASK = 0b11111111;
    constexpr auto BYTE_SIZE = 8;

    // Сохраним все байты в массив в обратном порядке.
    uint8_t bytes[TYPE_SIZE];
    // В цикле сохраняем младший байт в массив, и отбрасываем его сдвигом вправо.
    for(size_t i = 0; i < TYPE_SIZE; i++){
        bytes[TYPE_SIZE - i - 1] = ip & BYTE_MASK;
        ip >>= BYTE_SIZE;
    }

    // Собственно вывод полученного результата с разделителем.
    for(size_t i = 0; i < TYPE_SIZE; i++){
        if(i > 0)
            stream << '.';
        stream << unsigned(bytes[i]);
    }
}

/**
 * Функция вывода `условного` ip-адреса в поток stream.
 * Адрес представлен  в  виде контейнеров  `std::list` или `std::vector`.
 * Выводится содержимое контейнера поэлементно и разделяется символом `.` (точка).
 * */
template <typename Container, typename Iterator = typename std::iterator_traits<typename Container::const_iterator>>
void print_ip(std::ostream& stream, const Container& vector){
    bool first = true;
    for(const auto& i : vector){
        if(!first)
            stream << '.';

        first = false;
        stream << i;
    }
}

// TODO: Вывод адреса, если он представлен в виде `std::tuple` при условии, что все типы одинаковы.
template<typename T, size_t tuple_size = std::tuple_size<T>::value>
void print_ip(std::ostream& stream, const T& tuple){
   for(size_t i = 0; i < tuple_size; i++){
        if(i > 0)
            stream << '.';
        stream << std::get<i>(tuple); // Это не скомпилируется, потому что работает только в рантайме.
    }
}

/**
 * Вывод ip-адреса, если он задан в виде строки.
 * Выводится как есть.
 * */
void print_ip(std::ostream& stream, const std::string& ip){
    stream << ip;
 }

int main(){
//    std::cout << "Version: " << PROJECT_VERSION_PATCH << std::endl;
    print_ip(std::cout, char(-1));
    std::cout << std::endl;
    print_ip(std::cout, short(0));
    std::cout << std::endl;
    print_ip(std::cout, int(2130706433));
    std::cout << std::endl;
    print_ip(std::cout, long(8875824491850138409));
    std::cout << std::endl;
    
    print_ip(std::cout, std::string("192.168.0.1"));
    std::cout << std::endl;
    
    print_ip(std::cout, std::vector{10, 10, 0, 5});
    std::cout << std::endl;
    print_ip(std::cout, std::list{12, 10, 3, 4});
    std::cout << std::endl;

    // TODO: Вывод адреса, если он задан в виде tuple.
    //print_ip(std::cout, std::make_tuple(1, 2, 3, 14));

    return 0;
}