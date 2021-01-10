#pragma once
#include <boost/filesystem.hpp>
#include <unordered_set>

namespace fs = boost::filesystem;
using di = fs::recursive_directory_iterator;
using strings = std::vector<std::string>;
using unique_strings = std::unordered_set<std::string>;

class FileFinder;

class FileFinder
{
    friend class FileFinderIterator;
    class FileFinderIterator : public std::forward_iterator_tag
    {
    public:
        FileFinderIterator() = delete;
        explicit FileFinderIterator(FileFinder *ff) noexcept;
        void operator++() noexcept;
        const di& operator*() const noexcept;
        bool operator!=(const FileFinderIterator &) const noexcept;

    private:
        void control_depth(di &it) noexcept;

        [[nodiscard]] bool is_valid_file(const di&) const noexcept;
        [[nodiscard]] bool is_end_iterator(const di&) const noexcept;

    private:
        // TODO: переделать на weak_ptr
        FileFinder *finder;
        di current;
        unique_strings::const_iterator directory;
    };

public:
    FileFinder() = delete;
    FileFinder(FileFinder &&) = delete;

    FileFinder(const strings &paths, size_t level);

    void set_excluded_directories(const strings &paths) noexcept;

    FileFinderIterator begin();
    FileFinderIterator end();

private:
    const unique_strings directories;
    size_t level = 0;
    unique_strings excluded_directories;
};
