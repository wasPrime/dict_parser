#pragma once

#include "base_type.h"

namespace parser {

class Uint32 : public BaseType {
public:
    uint32_t value;

    virtual const std::string to_string() const override { return std::to_string(value); }

    virtual ~Uint32() {}
};

}  // namespace parser
