#include "dict_format/dict_format.h"

#include <gtest/gtest.h>

#include "data_define/builtin/array.h"
#include "data_define/builtin/float.h"
#include "data_define/builtin/int.h"
#include "data_define/builtin/string.h"
#include "data_define/builtin/uint32.h"
#include "data_define/builtin/uint64.h"
#include "data_define/custom_data/test_data.h"
#include "system/system_boost.h"
#include "utils/utils.h"

namespace parser {

TEST(DictFormatTest, ParseInt) {  // NOLINT
    const std::string str = "1";
    std::shared_ptr<BaseType> data = nullptr;
    int ret = parse<Int>(str, data);
    ASSERT_EQ(ret, SUCCESS);

    Int* data_int = dynamic_cast<Int*>(data.get());
    ASSERT_NE(data_int, nullptr);

    ASSERT_EQ(data_int->value, std::stoi(str));
}

TEST(DictFormatTest, ParseFloat) {  // NOLINT
    const std::string str = "1.0";
    std::shared_ptr<BaseType> data = nullptr;
    int ret = parse<Float>(str, data);
    ASSERT_EQ(ret, SUCCESS);

    auto* data_float = dynamic_cast<Float*>(data.get());
    ASSERT_NE(data_float, nullptr);

    ASSERT_EQ(data_float->value, std::stof(str));
}

TEST(DictFormatTest, ParseUint32) {  // NOLINT
    const std::string str = "1";
    std::shared_ptr<BaseType> data = nullptr;
    int ret = parse<Uint32>(str, data);
    ASSERT_EQ(ret, SUCCESS);

    auto* data_uint32 = dynamic_cast<Uint32*>(data.get());
    ASSERT_NE(data_uint32, nullptr);

    ASSERT_EQ(data_uint32->value, std::stoul(str));  // 没有 std::stou 故使用 std::stoul 代替
}

TEST(DictFormatTest, ParseUint64) {  // NOLINT
    const std::string str = "1";
    std::shared_ptr<BaseType> data = nullptr;
    int ret = parse<Uint64>(str, data);
    ASSERT_EQ(ret, SUCCESS);

    auto* data_uint64 = dynamic_cast<Uint64*>(data.get());
    ASSERT_NE(data_uint64, nullptr);

    ASSERT_EQ(data_uint64->value, std::stoul(str));
}

TEST(DictFormatTest, ParseString) {  // NOLINT
    const std::string str = "1 a";
    std::shared_ptr<BaseType> data = nullptr;
    int ret = parse<String>(str, data);
    ASSERT_EQ(ret, SUCCESS);

    auto* data_string = dynamic_cast<String*>(data.get());
    ASSERT_NE(data_string, nullptr);

    ASSERT_EQ(data_string->value, str);
}

TEST(DictFormatTest, ParseArrayInt) {  // NOLINT
    std::vector<int> int_vec{1, 2, 3};
    std::vector<std::string> str_vec;
    str_vec.reserve(int_vec.size());
    for (const int& i : int_vec) {
        str_vec.emplace_back(std::to_string(i));
    }
    const std::string str = std::to_string(int_vec.size()) + ":" + boost::join(str_vec, ",");
    std::shared_ptr<BaseType> data = nullptr;
    int ret = parse_array<Int>(str, data);
    ASSERT_EQ(ret, SUCCESS);

    auto* data_array_int = dynamic_cast<Array<Int>*>(data.get());
    ASSERT_NE(data_array_int, nullptr);
    ASSERT_EQ(data_array_int->value.size(), int_vec.size());

    for (int i = 0, n = data_array_int->value.size(); i < n; ++i) {
        ASSERT_EQ(data_array_int->value[i].value, int_vec[i]);
    }
}

TEST(DictFormatTest, ParseTestData) {  // NOLINT
    int v1 = 1;
    std::string v2 = "test_data";
    const std::string str = std::to_string(v1) + "|" + v2;
    std::shared_ptr<BaseType> data = nullptr;
    int ret = TestData::parse(str, data);
    ASSERT_EQ(ret, SUCCESS);
    auto* data_test_data = dynamic_cast<TestData*>(data.get());
    ASSERT_NE(data_test_data, nullptr);
    ASSERT_EQ(data_test_data->v1, v1);
    ASSERT_EQ(data_test_data->v2, v2);
}

}  // namespace parser
