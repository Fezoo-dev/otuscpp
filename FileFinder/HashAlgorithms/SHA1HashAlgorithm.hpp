#pragma once
#include "IHashAlgorithm.hpp"
#include "boost/uuid/name_generator_sha1.hpp"

class SHA1HashAlgorithm final : public IHashAlgorithm
{
public:
    [[nodiscard]] virtual std::string hash(const char *) noexcept override;
    virtual ~SHA1HashAlgorithm() override = default;

private:
    boost::uuids::name_generator_sha1 generator{boost::uuids::ns::dns()};
};