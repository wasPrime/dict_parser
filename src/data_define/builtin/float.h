#pragma once

#include "base_type.h"
#include "system/system_boost.h"

namespace parser {

class Float : public BaseType {
public:
    float value;

    virtual const std::string to_string() const override {
        return boost::lexical_cast<std::string>(value);
    }

    virtual ~Float() {}
};

}  // namespace parser
