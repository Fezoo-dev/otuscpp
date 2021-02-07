#include "FileFinderIterator.hpp"

FileFinder::FileFinderIterator::FileFinderIterator(std::shared_ptr<FileFinder> file_finder) noexcept
    : finder{std::move(file_finder)}
{
    if (finder == nullptr)
        return;
    directory = finder->directories.begin();
    operator++();
}

bool FileFinder::FileFinderIterator::is_end(const di &it) const noexcept
{
    return it == FileFinder::FileFinderIterator::end_iterator;
}

void FileFinder::FileFinderIterator::control_depth(di &it) noexcept
{
    if (!is_end(it) && static_cast<size_t>(it.depth()) >= finder->depth)
        it.disable_recursion_pending();
}

bool FileFinder::FileFinderIterator::is_valid_file(const di &it) const noexcept
{
    if(is_end(it))
        return false;

    for(const auto& validator : finder->validators)
    {
        if (!validator->validate(it))
            return false;
    }

    return true;
}

const di &FileFinder::FileFinderIterator::operator*() const noexcept
{
    return current;
}

bool FileFinder::FileFinderIterator::operator!=(const FileFinder::FileFinderIterator &other) const noexcept
{
    return current != other.current;
}

void FileFinder::FileFinderIterator::operator++() noexcept
{
    do
    {
        if (is_end(current))
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
            try
            {
                current++;
            }
            catch(...){}
        }

        control_depth(current);

    } while (!is_valid_file(current));
}