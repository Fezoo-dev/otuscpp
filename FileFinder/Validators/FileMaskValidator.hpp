#pragma once
#include "IFileValidator.hpp"
#include <boost/regex.hpp>
using strings = std::vector<std::string>;

/**
 * Фильтр поиска имён файлов по маске. Проверяется ТОЛЬКО имя файла.
 * ? - один символ. * - любое количество символов.
 * "te??.*" => "test.txt", "temp.tmp", "tell.me"
 * */
class FileMaskValidator : public IFileValidator
{
public:
    explicit FileMaskValidator(strings masks) noexcept;
    [[nodiscard]] bool validate(const di &it) const noexcept override;

private:
    std::vector<boost::regex> regexps;
};