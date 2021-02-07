#pragma once
#include <boost/filesystem.hpp>
#include "HashAlgorithms/IHashAlgorithm.hpp"

namespace fs = boost::filesystem;
using entry = fs::directory_entry;

struct ReadingStruct
{
    entry data;
    std::streamoff read_position = 0;
    const size_t block_size;
    char *buffer;
    bool ended = false;

    ReadingStruct(size_t block_size) : block_size{block_size}
    {
        buffer = (char *)malloc(block_size);
    }

    ~ReadingStruct()
    {
        free(buffer);
    }
    //buffer{std::make_unique<char *>(block_size)}{}
};

struct FileComparerNode
{
    entry data;
    std::string hash{0};
    std::string last_hash{0};
    std::unique_ptr<ReadingStruct> reading_struct;

    std::vector<entry> ended;
    std::vector<std::unique_ptr<FileComparerNode>> not_ended;

    FileComparerNode(entry &&data, size_t block_size);

    void read_next_hash(IHashAlgorithm &) noexcept;
};
