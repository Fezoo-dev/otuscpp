#include <cassert>
#include <cstdlib>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

#include "ippool.h"

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char d)
{
    std::vector<std::string> r;

    std::string::size_type start = 0;
    std::string::size_type stop = str.find_first_of(d);
    while (stop != std::string::npos)
    {
        r.emplace_back(str.substr(start, stop - start));

        start = stop + 1;
        stop = str.find_first_of(d, start);
    }

    r.emplace_back(str.substr(start));

    return r;
}

auto filter_for_equality_by_n_byte(const IPPool &pool, size_t n, int first_byte)
{
    return pool.filter([first_byte, n](const IPv4 &ip) { return ip[n] == first_byte; });
}

auto filter_for_equality_by_first_byte(const IPPool &pool, int first_byte)
{
    return pool.filter([first_byte](const IPv4 &ip) { return ip[0] == first_byte; });
}

auto filter_for_equality_by_first_two_bytes(const IPPool &pool, int first_byte, int second_byte)
{
    return pool.filter([first_byte, second_byte](const IPv4 &ip) { return ip[0] == first_byte && ip[1] == second_byte; });
}

auto filter_for_equality_with_any_byte(const IPPool &pool, int find_value)
{
    return pool.filter([find_value](const IPv4 &ip) {
        for (size_t i = 0; i < ip.size(); i++)
            if (ip[i] == find_value)
                return true;
        return false;
    });
}

int main()
{
    try
    {
        IPPool ip_pool;

        for (std::string line; std::getline(std::cin, line);)
        {
            auto v = split(line, '\t');
            ip_pool.push_back(split(v.at(0), '.'));
        }

        // Reverse lexicographically sort.
        std::sort(ip_pool.begin(), ip_pool.end(), std::greater<IPv4>());
        //
        for (const auto &ip : ip_pool)
            std::cout << ip << std::endl;

        // 222.173.235.246
        // 222.130.177.64
        // 222.82.198.61
        // ...
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // make filter by first byte.
        auto filter_by_first_byte = filter_for_equality_by_first_byte(ip_pool, 1);

        // print it.
        // std::cout << filter_by_first_byte;
        // The line above is equivalent to the next piece of code below, but for_each is more powerful!
        filter_by_first_byte.for_each(
            [](const auto& ip)
            {
                std::cout << ip << std::endl;
            });
        // 1.231.69.33
        // 1.87.203.225
        // 1.70.44.170
        // 1.29.168.152
        // 1.1.234.8

        // filter by first and second bytes and output
        auto filter_by_first_and_second_bytes = filter_for_equality_by_first_two_bytes(ip_pool, 46, 70);
        std::cout << filter_by_first_and_second_bytes;
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76

        // filter by any byte and output
        auto filter_by_any_byte = filter_for_equality_with_any_byte(ip_pool, 46);
        std::cout << filter_by_any_byte;
        // 186.204.34.46
        // 186.46.222.194
        // 185.46.87.231
        // 185.46.86.132
        // 185.46.86.131
        // 185.46.86.131
        // 185.46.86.22
        // 185.46.85.204
        // 185.46.85.78
        // 68.46.218.208
        // 46.251.197.23
        // 46.223.254.56
        // 46.223.254.56
        // 46.182.19.219
        // 46.161.63.66
        // 46.161.61.51
        // 46.161.60.92
        // 46.161.60.35
        // 46.161.58.202
        // 46.161.56.241
        // 46.161.56.203
        // 46.161.56.174
        // 46.161.56.106
        // 46.161.56.106
        // 46.101.163.119
        // 46.101.127.145
        // 46.70.225.39
        // 46.70.147.26
        // 46.70.113.73
        // 46.70.29.76
        // 46.55.46.98
        // 46.49.43.85
        // 39.46.86.85
        // 5.189.203.46
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    return 0;
}
