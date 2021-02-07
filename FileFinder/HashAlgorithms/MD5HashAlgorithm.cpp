#include "MD5HashAlgorithm.hpp"

std::string MD5HashAlgorithm::hash(const char *string) noexcept
{
    auto uuid = generator(string);
    return {uuid.begin(), uuid.end()};
}