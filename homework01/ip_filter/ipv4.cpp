#include "ipv4.h"
#include <tuple>

IpV4::IpV4(const IpV4StringVector& ipv4Vector) : data(ipv4Vector.size())
{
    if (data.size() != 4)
        throw std::out_of_range("invalid ctor data");

    for (size_t i = 0; i < data.size(); i++)
    {
        data[i] = std::stoi(ipv4Vector[i]);
        if (data[i] < 0 || data[i] > 255)
            throw std::invalid_argument("byte parse error");
    }
}

int IpV4::operator[](size_t index) const {
    if (index >= data.size())
        throw std::out_of_range("invalid data index");

    return data.at(index);
}

size_t IpV4::size() const {
    return data.size();
}

bool IpV4::operator<(const IpV4& otherIp) const
{
    return std::tie(data.at(0), data.at(1), data.at(2), data.at(3))
        < std::tie(otherIp.data.at(0), otherIp.data.at(1), otherIp.data.at(2), otherIp.data.at(3));
}

bool IpV4::operator==(const IpV4& otherIp) const
{
    return std::tie(data.at(0), data.at(1), data.at(2), data.at(3))
        == std::tie(otherIp.data.at(0), otherIp.data.at(1), otherIp.data.at(2), otherIp.data.at(3));
}

std::ostream& operator<<(std::ostream& stream, const IpV4& ip)
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
