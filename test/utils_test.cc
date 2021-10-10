#include "utils/utils.h"

#include <gtest/gtest.h>

#include <utility>

namespace parser {

class UtilsTest : public testing::Test {
protected:
    struct StringTestHelper {
        std::vector<std::string> factor;  // 拼接因子
        std::string delimiter;            // 连接符

        std::string spliced_string;  // 拼接后的字符串

        StringTestHelper(std::vector<std::string>&& factor_, std::string&& delimiter_,
                         std::string&& spliced_string_)
            : factor(factor_), delimiter(delimiter_), spliced_string(spliced_string_) {}
    };

    static void SetUpTestCase() {
        _s_helper_vec.emplace_back(
            StringTestHelper(std::vector<std::string>{"Hello", "World"}, "|", "Hello|World"));
    }

    static void TearDownTestCase() {}

    static std::vector<StringTestHelper> _s_helper_vec;
};

std::vector<UtilsTest::StringTestHelper> UtilsTest::_s_helper_vec;

TEST_F(UtilsTest, StringSplit) {
    for (auto& helper : _s_helper_vec) {
        const std::vector<std::string> real_factor =
            Utils::string_split(helper.spliced_string, helper.delimiter);
        const std::vector<std::string>& expect_factor = helper.factor;
        ASSERT_EQ(real_factor.size(), expect_factor.size());
        for (size_t i = 0, len = real_factor.size(); i < len; ++i) {
            ASSERT_EQ(real_factor[i], expect_factor[i]);
        }
    }
}

TEST_F(UtilsTest, StringJoin) {
    for (auto& helper : _s_helper_vec) {
        const std::string real =
            Utils::string_join(helper.factor.begin(), helper.factor.end(), helper.delimiter);
        const std::string& expect = helper.spliced_string;
        ASSERT_EQ(real, expect);
    }
}

}  // namespace parser
