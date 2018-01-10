#include <parserlog.native/core/Parser.hpp>

#include <gtest/gtest.h>

//--------------------------------------------------
using namespace parserlog::native::core;

class Parser_test
    :public ::testing::Test
{
public:
    void SetUp()
    {}
};

TEST_F(Parser_test, isLogFormat_false_empty)
{
    ASSERT_EQ(false, isLogFormat(""));
}

TEST_F(Parser_test, isLogFormat_false_short)
{
    ASSERT_EQ(false, isLogFormat("asd\tasda"));
}

TEST_F(Parser_test, isLogFormat_false_long)
{
    ASSERT_EQ(false, isLogFormat("asd\tasda\tasdasd\tadsadqwe\tasdasd"));
}

TEST_F(Parser_test, isLogFormat_false_hex)
{
    ASSERT_EQ(false, isLogFormat("0x000\tasda\tasdasd\tadsadqwe\tasdasd"));
}

TEST_F(Parser_test, isLogFormat_false_hex2)
{
    ASSERT_EQ(false, isLogFormat("0x000\tasda\t0xaaaa\tadsadqwe\tasdasd"));
}

TEST_F(Parser_test, isLogFormat_true1)
{
    ASSERT_EQ(true, isLogFormat("asd\t0x000"));
}

TEST_F(Parser_test, isLogFormat_true2)
{
    ASSERT_EQ(true, isLogFormat("asd\t0x000\tasdsd"));
}

TEST_F(Parser_test, GetLineInfo_empty)
{
    auto line = GetLineInfo("");
    ASSERT_EQ(0, line.m_ThreadId);
}

TEST_F(Parser_test, GetLineInfo_not_format)
{
    auto line = GetLineInfo("0\t0\t0\t0\t");
    ASSERT_EQ(0, line.m_ThreadId);
}

TEST_F(Parser_test, GetLineInfo_simple_format)
{
    auto line = GetLineInfo("1:2:3.4\t0x1\tSTR1\tSTR2");
    ASSERT_EQ(1, line.m_TimeStamp.tm_hour);
    ASSERT_EQ(2, line.m_TimeStamp.tm_min);
    ASSERT_EQ(3, line.m_TimeStamp.tm_sec);
    ASSERT_EQ(1, line.m_ThreadId);
    ASSERT_STREQ("STR1", line.m_Type.c_str());
    ASSERT_STREQ("STR2" , line.m_Component.c_str());
}