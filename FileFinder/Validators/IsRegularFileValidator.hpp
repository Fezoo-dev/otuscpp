#pragma once
#include "IFileValidator.hpp"

struct IsRegularFileValidator : public IFileValidator
{
    [[nodiscard]] bool validate(const di &it) const noexcept override;
};