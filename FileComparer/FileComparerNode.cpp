#include "FileComparerNode.hpp"
#include <iostream>

FileComparerNode::FileComparerNode(entry &&data, size_t block_size)
: data{data}
, reading_struct{std::make_unique<ReadingStruct>(block_size)}
{
}

void FileComparerNode::read_next_hash(IHashAlgorithm &hash_algorithm) noexcept
{
    memset(reading_struct->buffer, 0, reading_struct->block_size);
    try
    {
        /**
         * Читать надо двоичные данные, поэтому будем использовать
         * дескрипторы, так как они работают быстрее, чем потоки.
         * */
        FILE *file = fopen(data.path().c_str(), "r");
        fseek(file, reading_struct->read_position, SEEK_SET);
        fgets(reading_struct->buffer, reading_struct->block_size, file);
        reading_struct->read_position = ftell(file);
        reading_struct->ended = feof(file);
        fclose(file);
    }
    catch (...)
    {
        reading_struct->ended = true;
    }

    last_hash = hash_algorithm.hash(reading_struct->buffer);
    hash += last_hash;
}
