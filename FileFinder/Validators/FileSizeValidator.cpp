#include "FileSizeValidator.hpp"

FileSizeValidator::FileSizeValidator(size_t minimum_size_in_bytes) noexcept
: minimum_size{minimum_size_in_bytes}
{
}

bool FileSizeValidator::validate(const di &it) const noexcept
{
    return fs::file_size((*it).path()) >= minimum_size;
}