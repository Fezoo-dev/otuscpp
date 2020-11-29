#include <iostream>
#include <string>
#include <vector>

using IPv4StringVector = std::vector<std::string>;

class IPv4
{
public:
    IPv4(const IPv4StringVector& ipv4Vector);

    int operator[](size_t index) const;
    size_t size() const;

    bool operator<(const IPv4&) const;
    bool operator>(const IPv4&) const;
    bool operator==(const IPv4&) const;

    friend std::ostream& operator<<(std::ostream&, const IPv4&);

private:
    std::vector<int> data;
};