#include <iostream>
#include <boost/filesystem.hpp>
#include "CommandLineParser.hpp"
#include "FileFinder/FileFinderBuilder.hpp"
#include "FileComparer/FileComparer.hpp"

#include "HashAlgorithms/IHashAlgorithm.hpp"
#include "HashAlgorithms/NotHashAlgorithm.hpp"
#include "HashAlgorithms/MD5HashAlgorithm.hpp"
#include "HashAlgorithms/SHA1HashAlgorithm.hpp"

int main(int argc, char **argv)
{
    // Возможные алгоритмы хэширования.
    std::map<std::string, std::shared_ptr<IHashAlgorithm>> hashes =
        {
            {"md5", std::make_shared<MD5HashAlgorithm>()},
            {"sha1", std::make_shared<SHA1HashAlgorithm>()}};

    std::vector<std::string> available_hashes{hashes.size()};
    for (const auto &kv : hashes)
        available_hashes.push_back(kv.first);

    // Парсер должен знать возможные алгоритмы хэширования.
    CommandLineParser parser{std::move(available_hashes)};;

    if (!parser.parse(argc, argv, std::cerr))
        return 1;

    // Если не был указан алгоритм, используем фейковый, который ничего не хеширует.
    std::shared_ptr<IHashAlgorithm> algorithm;
    if(hashes.count(parser.get_algorithm()))
        algorithm = hashes[parser.get_algorithm()];
    else
        algorithm = std::make_shared<NotHashAlgorithm>();


    FileComparer file_comparer{algorithm, parser.get_block_size()};

    auto file_finder = FileFinderBuilder::build(parser);
    for (auto &entry : *file_finder)
    {
        //std::cout << *entry << std::endl;
        file_comparer.add_di(std::move(*entry));
    }
    //std::cout << "end" << std::endl;
    file_comparer.print();

    return 0;
}
