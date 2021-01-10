#include "FileFinder.hpp"

FileFinder::FileFinderIterator::FileFinderIterator(FileFinder* ff) : finder{ff}
{
}

FileFinder::FileFinderIterator& FileFinder::FileFinderIterator::end()
{

}

void FileFinder::FileFinderIterator::operator++()
{

}

    // FileFinder::FileFinderIterator &FileFinder::FileFinderIterator::operator++()
    // {
    //     return *this;
    // }

    // const FileFinder &FileFinder::FileFinderIterator::operator*() const
    // {
    //     return ff;
    // }

    // bool FileFinder::FileFinderIterator::operator!=(const FileFinderIterator &rhs) const
    // {
    //     (void)rhs;
    //     return true;
    // }
