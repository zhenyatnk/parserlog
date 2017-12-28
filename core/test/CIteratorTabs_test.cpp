#include <gtest/gtest.h>
#include <parserlog/core/IteratorImpls.hpp>
#include <future>

//--------------------------------------------------------------------------------------------------------------------------------------
using namespace parserlog::core;

class CIteratorTabs_test
    :public ::testing::Test
{
public:
    void SetUp()
    {}
};

TEST_F(CIteratorTabs_test, empty_source_1)
{
    std::string buffer = "";
    auto iterator = CreateIteratorTabs(buffer);
    ASSERT_EQ(false, iterator->next());
}

TEST_F(CIteratorTabs_test, empty_source_2)
{
    std::string buffer = "\t";
    auto iterator = CreateIteratorTabs(buffer);
    ASSERT_EQ(true, iterator->next());
    ASSERT_STREQ("", iterator->current().c_str());
}

TEST_F(CIteratorTabs_test, start_delims)
{
    std::string buffer = "\ta";
    auto iterator = CreateIteratorTabs(buffer);
    ASSERT_EQ(true, iterator->next());
    ASSERT_EQ(true, iterator->next());
    ASSERT_STREQ("a", iterator->current().c_str());
}

TEST_F(CIteratorTabs_test, one_symbol)
{
    std::string buffer = "a";
    auto iterator = CreateIteratorTabs(buffer);
    ASSERT_EQ(true, iterator->next());
    ASSERT_STREQ("a", iterator->current().c_str());
    ASSERT_EQ(false, iterator->next());
}

TEST_F(CIteratorTabs_test, many_symbols_1)
{
    std::string buffer = "asb";
    auto iterator = CreateIteratorTabs(buffer);
    ASSERT_EQ(true, iterator->next());
    ASSERT_STREQ("asb", iterator->current().c_str());
    ASSERT_EQ(false, iterator->next());
}

TEST_F(CIteratorTabs_test, start_end_delim_many_symbols_1)
{
    std::string buffer = "a\tb\tc";
    auto iterator = CreateIteratorTabs(buffer);
    ASSERT_EQ(true, iterator->next());
    ASSERT_EQ(true, iterator->next());
    ASSERT_EQ(true, iterator->next());
    ASSERT_STREQ("c", iterator->current().c_str());
    ASSERT_EQ(false, iterator->next());
}
