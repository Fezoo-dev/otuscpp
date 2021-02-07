#include "FileMaskValidator.hpp"
#include <boost/algorithm/string/replace.hpp>

FileMaskValidator::FileMaskValidator(strings masks) noexcept
{
    std::transform(
        std::move_iterator(masks.begin()),
        std::move_iterator(masks.end()),
        std::back_inserter(regexps),
        [](auto it) {
            boost::algorithm::replace_all(it, ".", "[.]");
            boost::algorithm::replace_all(it, "*", ".*");
            boost::algorithm::replace_all(it, "?", ".");

            return boost::regex{it, boost::regex::icase};
        });
}

bool FileMaskValidator::validate(const di &it) const noexcept
{
    auto &path = (*it).path().filename().string();
    for (const auto &filter : regexps)
        if (boost::regex_match(path, filter))
            return true;

    return false;
}