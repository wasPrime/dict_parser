/**
 * @file    utils.hpp
 * @author  wenshishi
 * @brief   工具类
 **/

#pragma once

#include "utils.h"

namespace parser {

template <typename Iter>
const std::string Utils::string_join(const Iter begin, const Iter end,
                                     const std::string& connector) {
    std::stringstream ss;
    if (begin != end) {
        Iter elem = begin;
        ss << *elem;
        ++elem;
        for (; elem != end; ++elem) {
            ss << connector;
            ss << *elem;
        }
    }
    return ss.str();
}

}  // namespace parser
