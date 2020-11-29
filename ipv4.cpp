#include "ipv4.h"
#include <tuple>

IPv4::IPv4(const IPv4StringVector& ipv4Vector)
{
    if (ipv4Vector.size() != 4)
        throw std::out_of_range("invalid ctor data");

    data.reserve(4);
    for (size_t i = 0; i < ipv4Vector.size(); i++)
    {
        data.emplace_back(std::stoi(ipv4Vector[i]));
        if (data[i] < 0 || data[i] > 255)
            throw std::invalid_argument("byte parse error");
    }
}

int IPv4::operator[](size_t index) const {
    if (index >= data.size())
        throw std::out_of_range("invalid data index");

    return data.at(index);
}

size_t IPv4::size() const {
    return data.size();
}

bool IPv4::operator<(const IPv4& otherIp) const
{
    return data < otherIp.data;
}

bool IPv4::operator>(const IPv4& otherIp) const
{
    return data > otherIp.data;
}

bool IPv4::operator==(const IPv4& otherIp) const
{
    return data == otherIp.data;
}

std::ostream& operator<<(std::ostream& stream, const IPv4& ip)
{
    bool start = true;
    for (auto& byte : ip.data)
    {
        if (!start)
            std::cout << '.';

        start = false;
        std::cout << byte;
    }
    return stream;
}
