#include <gtest/gtest.h>

#include "data_define/builtin/array.h"
#include "data_define/builtin/float.h"
#include "data_define/builtin/int.h"
#include "data_define/builtin/string.h"
#include "data_define/builtin/uint32.h"
#include "data_define/builtin/uint64.h"
#include "data_define/custom_data/test_data.h"

namespace parser {

class DataDefineTest : public testing::Test {
protected:
    static void SetUpTestCase() {}

    static void TearDownTestCase() {}

    static const int TEST_VALUE_INT;
    static const float TEST_VALUE_FLOAT;
    static const uint32_t TEST_VALUE_UINT32_T;
    static const uint64_t TEST_VALUE_UINT64_T;
    static const std::string TEST_VALUE_STRING;
};

const int DataDefineTest::TEST_VALUE_INT = 1;
const float DataDefineTest::TEST_VALUE_FLOAT = 1.0F;
const uint32_t DataDefineTest::TEST_VALUE_UINT32_T = 1U;
const uint64_t DataDefineTest::TEST_VALUE_UINT64_T = 1U;
const std::string DataDefineTest::TEST_VALUE_STRING = "test value";

TEST_F(DataDefineTest, Int) {
    Int i;
    i.value = TEST_VALUE_INT;
    ASSERT_EQ(i.to_string(), std::to_string(TEST_VALUE_INT));
}

TEST_F(DataDefineTest, Float) {
    Float f;
    f.value = TEST_VALUE_FLOAT;
    ASSERT_EQ(f.to_string(), std::to_string(TEST_VALUE_FLOAT));
}

TEST_F(DataDefineTest, Uint32) {
    Uint32 uint32;
    uint32.value = TEST_VALUE_UINT32_T;
    ASSERT_EQ(uint32.to_string(), std::to_string(TEST_VALUE_UINT32_T));
}

TEST_F(DataDefineTest, Uint64) {
    Uint64 uint64;
    uint64.value = TEST_VALUE_UINT64_T;
    ASSERT_EQ(uint64.to_string(), std::to_string(TEST_VALUE_UINT64_T));
}

TEST_F(DataDefineTest, String) {
    String str;
    str.value = TEST_VALUE_STRING;
    ASSERT_EQ(str.to_string(), TEST_VALUE_STRING);
}

TEST_F(DataDefineTest, Array) {
    Int i;
    i.value = TEST_VALUE_INT;

    Array<Int> array;
    array.value.emplace_back(std::move(i));
    ASSERT_EQ(array.to_string(), "[" + std::to_string(TEST_VALUE_INT) + "]");
}

TEST_F(DataDefineTest, TestData) {
    TestData test_data;
    test_data.v1 = TEST_VALUE_INT;
    test_data.v2 = TEST_VALUE_STRING;
    ASSERT_EQ(test_data.to_string(),
              "(" + std::to_string(TEST_VALUE_INT) + "|" + TEST_VALUE_STRING + ")");
}

}  // namespace parser
