#pragma once
#include <vector>
#include "IFileValidator.hpp"

using strings = std::vector<std::string>;

class ExcludeDirectoriesValidator : public IFileValidator
{
public:
    explicit ExcludeDirectoriesValidator(strings paths) noexcept;
    [[nodiscard]] bool validate(const di &it) const noexcept override;

private:
    strings excluded_directories;
};