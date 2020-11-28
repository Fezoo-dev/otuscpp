#include <iostream>
#include <string>
#include <vector>

using IpV4StringVector = std::vector<std::string>;

class IpV4
{
public:
    IpV4(const IpV4StringVector& ipv4Vector);

    int operator[](size_t index) const;
    size_t size() const;

    bool operator<(const IpV4&) const;
    bool operator==(const IpV4&) const;

    friend std::ostream& operator<<(std::ostream&, const IpV4&);

private:
    std::vector<int> data;
};