#include <iostream>
#include "CommandLineParser.hpp"
#include "boost/algorithm/string/join.hpp"

CommandLineParser::CommandLineParser(const strings &algorithms) noexcept : available_algorithms{std::move(algorithms)}
{
    visible_options.add_options()
        (CommandLineOptions::help, "This help.")
        (CommandLineOptions::exclude, po::value<strings>()->multitoken()->default_value({}, ""), "Exclude directory.")
        (CommandLineOptions::file_mask, po::value<strings>()->multitoken()->default_value({ "*" }, ""), "File masks.")
        (CommandLineOptions::block_size, po::value<size_t>()->default_value(1024), "Block size in bytes for read.")
        (CommandLineOptions::nesting_level, po::value<size_t>()->default_value(0), "Nesting level for search.")
        (CommandLineOptions::file_size, po::value<size_t>()->default_value(1), "Minimum size of file.")
        (CommandLineOptions::algorithm,  po::value<std::string>()->default_value(available_algorithms[0]), ("Hash algorithm: " + boost::algorithm::join(available_algorithms, ", ")).c_str())
        ;

    cmd_line_options.add(visible_options);
    cmd_line_options.add_options()
        (CommandLineOptions::dirs, po::value<strings>()->multitoken(), "Directories for scan.");
}

bool CommandLineParser::parse(int argc, char** argv, std::ostream& error_stream) noexcept
{
    bool parseResult = true;

    try
    {
        po::positional_options_description p;
        p.add(CommandLineOptions::dirs, -1);

        po::variables_map vm;
        po::store(
            po::command_line_parser(argc, argv)
            .options(cmd_line_options)
            .positional(p)
            .run(),
            vm);

        //po::notify(vm);

        move_strings(vm, CommandLineOptions::dirs, dirs);

        if (vm.count(CommandLineOptions::help) || dirs.size() == 0)
        {
            error_stream << std::string(argv[0]) << " [option [...]] path1 [path2 [...]]" << '\n';
            error_stream << visible_options;
            error_stream << "\nExample: \n"
                         << std::string(argv[0]) << " "
                         << "--" << CommandLineOptions::algorithm << "=md5 "
                         << "--" << CommandLineOptions::block_size << "=512 "
                         << "--" << CommandLineOptions::exclude << "=/home/ "
                         << "--" << CommandLineOptions::exclude << "=~/Downloads "
                         << "--" << CommandLineOptions::file_mask << "=*.txt "
                         << "--" << CommandLineOptions::file_mask << "=*.png "
                         << "--" << CommandLineOptions::file_size << "=10240 "
                         << "--" << CommandLineOptions::nesting_level << "=3 "
                         << "~/ /tmp" << '\n';
            return false;
        }
        move_strings(vm, CommandLineOptions::exclude, exclude_dirs);        
        move_strings(vm, CommandLineOptions::file_mask, file_masks);

        algorithm = std::move(vm[CommandLineOptions::algorithm].as<std::string>());

        block_size = vm[CommandLineOptions::block_size].as<size_t>();
        nesting_level = vm[CommandLineOptions::nesting_level].as<size_t>();
        minimum_file_size = vm[CommandLineOptions::file_size].as<size_t>();
    }
    catch (std::exception& e)
    {
        error_stream << e.what() << std::endl;
        parseResult = false;
    }

    return parseResult;
}

void CommandLineParser::move_strings(po::variables_map& vm, const char* key, strings& output) noexcept
{
    if (vm.count(key))
        output = std::move(vm[key].as<strings>());
}

const strings& CommandLineParser::get_directories() const noexcept
{
    return dirs;
}

const strings& CommandLineParser::get_exclude_directories() const noexcept
{
    return exclude_dirs;
}

const strings& CommandLineParser::get_file_masks() const noexcept
{
    return file_masks;
}

size_t CommandLineParser::get_block_size() const noexcept
{
    return block_size;
}

size_t CommandLineParser::get_minimum_file_size() const noexcept
{
    return minimum_file_size;
}

size_t CommandLineParser::get_nesting_level() const noexcept
{
    return nesting_level;
}

const std::string& CommandLineParser::get_algorithm() const noexcept
{
    return algorithm;
}

void CommandLineParser::remove_duplicates() noexcept
{
    dirs.erase(
        std::unique(dirs.begin(), dirs.end()),
        dirs.end());

    exclude_dirs.erase(
        std::unique(exclude_dirs.begin(), exclude_dirs.end()),
        exclude_dirs.end());

    file_masks.erase(
        std::unique(file_masks.begin(), file_masks.end()),
        file_masks.end());
}