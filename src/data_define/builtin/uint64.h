#pragma once

#include "base_type.h"

namespace parser {

class Uint64 : public BaseType {
public:
    uint64_t value;

    virtual const std::string to_string() const override { return std::to_string(value); }

    virtual ~Uint64() {}
};

}  // namespace parser
