#pragma once

#include "base_type.h"

namespace parser {

class Uint64 : public BaseType {
public:
    uint64_t value;

    [[nodiscard]] std::string to_string() const override { return std::to_string(value); }

    ~Uint64() override = default;
};

}  // namespace parser
