/**
 * @file    utils.cc
 * @author  wenshishi
 * @brief   工具类
 **/

#include "utils.h"

namespace parser {

const std::vector<std::string> Utils::string_split(const std::string& str,
                                                   const std::string& delimiter) {
    std::vector<std::string> ret;

    std::string::size_type last_pos = str.find_first_not_of(delimiter, 0);
    std::string::size_type pos = str.find_first_of(delimiter, last_pos);
    while (pos != std::string::npos || last_pos != std::string::npos) {
        ret.push_back(str.substr(last_pos, pos - last_pos));
        last_pos = str.find_first_not_of(delimiter, pos);
        pos = str.find_first_of(delimiter, last_pos);
    }

    return ret;
}

}  // namespace parser
