#include "SHA1HashAlgorithm.hpp"

std::string SHA1HashAlgorithm::hash(const char *string) noexcept
{
    auto uuid = generator(string);
    return {uuid.begin(), uuid.end()};
}