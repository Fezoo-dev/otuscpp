#pragma once
#include <set>

#include <boost/program_options.hpp>
namespace po = boost::program_options;

using strings = std::vector<std::string>;

class CommandLineParser
{
    struct CommandLineOptions
    {
        static inline const char help[] = "help";
        static inline const char dirs[] = "dirs";
        static inline const char exclude[] = "exclude";
        static inline const char nesting_level[] = "nesting";
        static inline const char file_mask[] = "mask";
        static inline const char block_size[] = "block";
        static inline const char algorithm[] = "algorithm";
        static inline const char file_size[] = "filesize";
    };

    public:
    explicit CommandLineParser(const strings& available_algorithms) noexcept;

    [[nodiscard]] bool parse(int argc, char **argv, std::ostream &) noexcept;
    [[nodiscard]] const strings &get_directories() const noexcept;
    [[nodiscard]] const strings &get_exclude_directories() const noexcept;
    [[nodiscard]] const strings &get_file_masks() const noexcept;
    [[nodiscard]] size_t get_block_size() const noexcept;
    [[nodiscard]] size_t get_nesting_level() const noexcept;
    [[nodiscard]] size_t get_minimum_file_size() const noexcept;
    [[nodiscard]] const std::string &get_algorithm() const noexcept;

    void
    remove_duplicates() noexcept;

private:
    void
    move_strings(po::variables_map &, const char *, strings &) noexcept;

private:
    po::options_description cmd_line_options;
    po::options_description visible_options{"Options"};

    strings available_algorithms;
    strings dirs;
    strings exclude_dirs;
    strings file_masks;
    std::string algorithm{0};
    size_t block_size;
    size_t nesting_level = 0;
    size_t minimum_file_size = 1;
};