#include "IHashAlgorithm.hpp"

class NotHashAlgorithm final : public IHashAlgorithm
{
    public:
    [[nodiscard]] std::string hash(const char* raw_string) noexcept override final
    {
        return raw_string;
    }

    ~NotHashAlgorithm() override = default;
};