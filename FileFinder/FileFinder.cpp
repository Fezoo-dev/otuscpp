#include "FileFinder.hpp"
#include <type_traits>
#include <iostream>

FileFinder::FileFinder(const strings &paths, size_t depth_level) noexcept
    : directories{paths.begin(), paths.end()},
      depth{depth_level}
{
}

FileFinder* FileFinder::add_validator(std::shared_ptr<IFileValidator> validator) noexcept
{
    validators.push_back(std::move(validator));
    return this;
}

FileFinder::FileFinderIterator FileFinder::begin()
{
    return FileFinder::FileFinderIterator{shared_from_this()};
}

FileFinder::FileFinderIterator FileFinder::end()
{
    return FileFinder::FileFinderIterator{nullptr};
}

