#include "utils.h"

namespace parser {

const std::vector<std::string> Utils::string_split(const std::string& str,
                                                   const std::string& delimiter) {
    std::vector<std::string> ret;

    size_t last = 0;
    size_t index = str.find_first_of(delimiter, last);
    while (index != std::string::npos) {
        ret.emplace_back(str.substr(last, index - last));
        last = index + delimiter.size();
        index = str.find_first_of(delimiter, last);
    }
    ret.emplace_back(str.substr(last, index - last));

    return ret;
}

}  // namespace parser
