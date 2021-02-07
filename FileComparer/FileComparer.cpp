#include "FileComparer.hpp"
#include <iostream>

FileComparer::FileComparer(std::shared_ptr<IHashAlgorithm>& alg, size_t block_size) : algorithm{alg}, block_size{block_size}
{
}

void FileComparer::print() const noexcept
{
    if(root)
        print(*root);
}

void FileComparer::print(const FileComparerNode& node) const noexcept
{
    if (node.ended.size() > 0)
    {
        std::cout << node.data.path().string() << std::endl;
        for (const auto &n : node.ended)
            std::cout << n.path().string() << std::endl;

        std::cout << std::endl;
    }

    for(const auto& n : node.not_ended)
        print(*n);
}

/**
 * Попытка вставить обёртку FileComparerNode new_node в узел node.
 * Сравниваются хеши либо до полного совпадения (тогда new_node помещается в ended к node),
 * либо до первого расхождения, тогда поиск будет продолжен рекурсивно либо в node.not_ended
 * (если хэш new_node совпал с кем-то), либо new_node будет просто добавлен в node.not_ended.
 * */
void FileComparer::add_di(std::unique_ptr<FileComparerNode> new_node, FileComparerNode &node) noexcept
{
    do
    {
        if (!new_node->reading_struct->ended)
            new_node->read_next_hash(*algorithm);

        if(!node.reading_struct->ended && node.hash.size() < new_node->hash.size())
            node.read_next_hash(*algorithm);

        auto hash_length = new_node->hash.size();
        if (memcmp(node.hash.c_str(), new_node->hash.c_str(), hash_length))
        {
            for(const auto& not_ended_node : node.not_ended)
            {
                if(memcmp(new_node->hash.c_str(), not_ended_node->hash.c_str(), hash_length) == 0)
                {
                    add_di(std::move(new_node), *not_ended_node);
                    return;
                }
            }
            node.not_ended.emplace_back(std::move(new_node));
            return;
        }

    } while (!new_node->reading_struct->ended || !node.reading_struct->ended);

    // Хэши совпадают.
    node.ended.emplace_back(new_node->data);
}

/**
 * Добавить новый файл в хранилище.
 * Запускает поиск подходящего места в дереве для вставки.
 * */
void FileComparer::add_di(entry &&entry) noexcept
{
    auto node = std::make_unique<FileComparerNode>(std::move(entry), block_size);
    if (!root)
    {
        root = std::move(node);
        return;
    }

    add_di(std::move(node), *root);
}
