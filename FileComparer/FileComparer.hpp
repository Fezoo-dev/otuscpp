#pragma once
#include <boost/filesystem.hpp>
#include "HashAlgorithms/IHashAlgorithm.hpp"
#include "FileComparerNode.hpp"

namespace fs = boost::filesystem;
using entry = fs::directory_entry;

//using namespace FileComparerData;

class FileComparer
{
public:
    explicit FileComparer(std::shared_ptr<IHashAlgorithm>& alg, size_t block_size);

    void add_di(entry &&entry) noexcept;

    void print() const noexcept;

private:
    void add_di(std::unique_ptr<FileComparerNode> new_node, FileComparerNode &node) noexcept;

    void read_block() noexcept;

    void print(const FileComparerNode&) const noexcept;

private:
    std::shared_ptr<IHashAlgorithm> algorithm;
    size_t block_size = 1;
    std::unique_ptr<FileComparerNode> root;
};
