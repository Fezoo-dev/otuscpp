#pragma once
#include <unordered_set>
#include "IFileValidator.hpp"

class FileSizeValidator : public IFileValidator
{
public:
    explicit FileSizeValidator(size_t minimum_size_in_bytes) noexcept;
    [[nodiscard]] bool validate(const di &it) const noexcept override;

private:
    size_t minimum_size = 1;
};