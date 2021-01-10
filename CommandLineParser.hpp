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
        static inline const char file_mask[] = "masks";
        static inline const char block_size[] = "block";
        static inline const char algorithm[] = "algorithm";
    };

    public:
    CommandLineParser();

    [[nodiscard]]
    bool parse(int argc, char** argv, std::ostream&) noexcept;
    [[nodiscard]]
    const strings& get_directories() const noexcept;
    [[nodiscard]]
    const strings& get_exclude_directories() const noexcept;
    [[nodiscard]]
    const strings& get_file_masks() const noexcept;
    [[nodiscard]]
    size_t get_block_size() const noexcept;
    [[nodiscard]]
    size_t get_nesting_level() const noexcept;

private:
    void move_strings(po::variables_map&, const char*, strings&) noexcept;
    
    private:
    po::options_description cmd_line_options;
    po::options_description visible_options{"Options"};
    
    strings dirs;
    strings exclude_dirs;
    strings file_masks;
    size_t block_size;
    size_t nesting_level;
};