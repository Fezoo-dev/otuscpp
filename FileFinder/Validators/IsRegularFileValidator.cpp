#include "IsRegularFileValidator.hpp"

bool IsRegularFileValidator::validate(const di &it) const noexcept
{
    return boost::filesystem::is_regular_file(it->status());
}