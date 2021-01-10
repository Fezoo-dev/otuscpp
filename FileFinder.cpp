#include "FileFinder.hpp"

FileFinder::FileFinder(const strings &paths, size_t level)
    : directories{paths.begin(), paths.end()},
      level{level}
{
}

void FileFinder::set_excluded_directories(const strings &paths) noexcept
{
    std::copy(paths.begin(), paths.end(),
              std::inserter(excluded_directories, excluded_directories.end()));
}

FileFinder::FileFinderIterator FileFinder::begin()
{
    return FileFinder::FileFinderIterator{this};
}

FileFinder::FileFinderIterator FileFinder::end()
{
    return FileFinder::FileFinderIterator{nullptr};
}

FileFinder::FileFinderIterator::FileFinderIterator(FileFinder *ff) noexcept
    : finder{ff}
{
    if(ff == nullptr)
        return;
    directory = finder->directories.begin();
    operator++();
}

bool FileFinder::FileFinderIterator::is_end_iterator(const di& it) const noexcept
{
    return it == fs::end(it);
}

void FileFinder::FileFinderIterator::control_depth(di &it) noexcept
{
    if (!is_end_iterator(it) && static_cast<size_t>(it.depth()) >= finder->level)
        it.disable_recursion_pending();
}

bool FileFinder::FileFinderIterator::is_valid_file(const di& it) const noexcept
{
    return !is_end_iterator(it) && fs::is_regular_file(it->status());
}

const di& FileFinder::FileFinderIterator::operator*() const noexcept
{
    return current;
}

bool FileFinder::FileFinderIterator::operator!=(const FileFinder::FileFinderIterator& other) const noexcept
{
    return current != other.current;
}

void FileFinder::FileFinderIterator::operator++() noexcept
{
    do
    {
        if (is_end_iterator(current))
        {
            if (directory != finder->directories.cend())
            {
                current = di(*directory);
                directory++;
            }
            else
            {
                break;
            }
        }
        else
        {
            current++;
        }

        control_depth(current);

    } while (!is_valid_file(current));
}