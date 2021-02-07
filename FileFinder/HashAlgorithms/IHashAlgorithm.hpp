#pragma once
#include <string>

struct IHashAlgorithm
{
    [[nodiscard]] virtual std::string hash(const char *) noexcept = 0;
    virtual ~IHashAlgorithm() = 0;
};