#pragma once
#include "InputParser.hpp"

struct InputParserBuilder
{
    [[nodiscard]]
    static InputParser build(std::string prefix, size_t static_container_size);
};