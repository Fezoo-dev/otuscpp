#pragma once

#include "FileFinder.hpp"
#include "../CommandLineParser.hpp"

#include "Validators/IsRegularFileValidator.hpp"
#include "Validators/ExcludeDirectoriesValidator.hpp"
#include "Validators/FileSizeValidator.hpp"
#include "Validators/FileMaskValidator.hpp"

class FileFinderBuilder
{
    public:
        static std::shared_ptr<FileFinder> build(CommandLineParser& parser)
        {
            parser.remove_duplicates();

            FileFinder* ff = new FileFinder(parser.get_directories(), parser.get_nesting_level());

            //std::vector<std::string> vvv = {"/home/fezoo/tmp", "/home/fezoo/Unity"};
            //std::vector<std::string> excluded = {};
            //{"/home/fezoo/tmp/0/1/2"};
            //std::vector<std::string> masks = {"*.cpp"}; //b*m*p

            //auto ff = std::make_shared<FileFinder>(vvv, 2);
            //auto ff = new FileFinder(vvv, 3);

            ff->add_validator(std::make_shared<IsRegularFileValidator>())
              ->add_validator(std::make_shared<FileSizeValidator>(parser.get_minimum_file_size()));

            if (parser.get_exclude_directories().size() > 0)
                ff->add_validator(std::make_shared<ExcludeDirectoriesValidator>(parser.get_exclude_directories()));

            if (parser.get_file_masks().size() > 0)
                ff->add_validator(std::make_shared<FileMaskValidator>(parser.get_file_masks()));

            return std::shared_ptr<FileFinder>(ff);
        }
};
