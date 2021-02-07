#pragma once
#include <boost/filesystem.hpp>
namespace fs = boost::filesystem;
using di = fs::recursive_directory_iterator;

struct IFileValidator
{
    [[nodiscard]] virtual bool validate(const di&) const noexcept = 0;
    virtual ~IFileValidator() = 0;
};
