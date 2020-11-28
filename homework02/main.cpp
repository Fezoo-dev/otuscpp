#include <iostream>
#include <map>

#include "version.hpp"
#include "reserve_allocator.cpp"
#include "strange_struct.cpp"

using namespace homework02;

namespace Factorial
{
    template <int n>
    struct factorial_compile_time
    {
        static_assert(n > 0);
        static const int value = n * factorial_compile_time<n - 1>::value;
    };

    template <>
    struct factorial_compile_time<0>
    {
        static const int value = 1;
    };

    // 11! = 39916800 is bigger than max int value.
    const int factorial_table[] = {
        factorial_compile_time<0>::value,
        factorial_compile_time<1>::value,
        factorial_compile_time<2>::value,
        factorial_compile_time<3>::value,
        factorial_compile_time<4>::value,
        factorial_compile_time<5>::value,
        factorial_compile_time<6>::value,
        factorial_compile_time<7>::value,
        factorial_compile_time<8>::value,
        factorial_compile_time<9>::value,
        factorial_compile_time<10>::value
    };

    int factorial(int N)
    {
        return factorial_table[N];
    }
} // namespace Factorial

using namespace Factorial;

template <typename Map>
void fill_map(Map& map) noexcept{
    for(int i = 0; i <= 9; i++)
        map.insert({i, factorial(i)});
}

template <typename Map>
void print_map(std::ostream& stream, const Map& map) noexcept{
    for(auto& [key, value] : map)
        stream << key << ' ' << value << '\n';
}

template <typename Container>
void fill_container(Container& contaiter) noexcept{
    for(int i = 0; i < 10; i++)
        contaiter.emplace_back(i);
}

template <typename Container>
void print_container(std::ostream& stream, const Container& map) noexcept{
    bool first = true;
    for(auto& item : map)
    {
        if(!first)
            stream << ' ';
        first = false;
        stream << item;
    }
    stream << '\n';
}

class Logger
{
private:
    int i;
public:
    Logger(int i);
    ~Logger();

    friend std::ostream& operator << (std::ostream& stream, const Logger& l){
        stream << "logger(" << l.i << ") ";
        stream << std::endl;
        return stream;
    }
};

Logger::Logger(int i) : i(i)
{
    std::cout << "Logger ctor " << i << std::endl;
}

Logger::~Logger()
{
    std::cout << "Logger destructor " << i << std::endl;
}



int main(){
    std::cout << "Version: " << PROJECT_VERSION_PATCH << std::endl;

    // создание экземпляра std::map<int, int>
    std::map<int, int> vanila_map;
    // заполнение 10 элементами, где ключ-это число от 0 до 9, а значение -факториал ключа
    fill_map(vanila_map);
    // выводить не просили, но если надо, то - вот.
    //print_map(std::cout, vanila_map);

    // создание  экземпляра std::map<int,  int>с  новым  аллокатором,ограниченным 10 элементами
    auto map10 = std::map<int, int, std::less<int>, reserve_allocator<std::pair<const int, int>, 10>>{};
    // заполнение 10 элементами, где ключ-это число от 0 до 9, а значение -факториал ключа
    fill_map(map10);
    // вывод на экран всех значений (ключ и значение разделены пробелом) хранящихся в контейнере
    print_map(std::cout, map10);

    // создание экземпляра своего контейнера для хранения значений типа int
    strange_struct<int> strange_int;
    //strange_struct<Logger> strange_int;
    // заполнение 10 элементами от 0 до 9
    fill_container(strange_int);
    // выводить не просили, но если надо, то - вот.
    std::cout << strange_int << std::endl;

    // создание экземпляра своего контейнера для хранения значений типа int с новым аллокатором,ограниченным 10 элементами
    strange_struct<int, reserve_allocator<int, 10>> strange_allocator_int;
    //strange_struct<Logger, reserve_allocator<Logger, 10>> strange_allocator_struct;
    // заполнение 10 элементами от 0 до 9
    fill_container(strange_allocator_int);
    // вывод на экран всех значений,хранящихся в контейнере
    std::cout << strange_allocator_int << std::endl;

    return 0;
}