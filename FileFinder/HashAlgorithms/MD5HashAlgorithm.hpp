#pragma once
#include "IHashAlgorithm.hpp"
#include "boost/uuid/name_generator_md5.hpp"

class MD5HashAlgorithm final : public IHashAlgorithm
{
public:
    [[nodiscard]] virtual std::string hash(const char *) noexcept override;
    virtual ~MD5HashAlgorithm() override = default;

private:
    boost::uuids::name_generator_md5 generator{boost::uuids::ns::dns()};
};