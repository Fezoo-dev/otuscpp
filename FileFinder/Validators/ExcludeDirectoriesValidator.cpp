#include "ExcludeDirectoriesValidator.hpp"


ExcludeDirectoriesValidator::ExcludeDirectoriesValidator(strings paths) noexcept
{
    std::move(
        std::move_iterator(paths.begin()),
        std::move_iterator(paths.end()),
        std::back_inserter(excluded_directories));
}

bool ExcludeDirectoriesValidator::validate(const di &it) const noexcept
{
    auto& path = (*it).path().native();
    for (const auto &filter : excluded_directories)
        if (path.find(filter) != std::string::npos)
            return false;
    
    return true;
}