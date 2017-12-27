#include <gtest/gtest.h>
#include <parserlog/core/IteratorImpls.hpp>
#include <future>

//--------------------------------------------------------------------------------------------------------------------------------------
using namespace parserlog::core;

namespace
{
std::string ConvertToString(baseex::core::IStream::Ptr aStream)
{
    uint8_t *lBuffer = new uint8_t[aStream->Size()];
    aStream->Read(0, lBuffer, aStream->Size());
    std::string lRet((char*)lBuffer, aStream->Size());
    delete[] lBuffer;
    return lRet;
}
std::string ConvertToString(baseex::core::ILinearStream::Ptr aStream)
{
    return std::string(aStream->GetBuff<const char*>(), aStream->Size());
}
}

class CIteratorBase_test
    :public ::testing::Test
{
public:
    void SetUp()
    {}
};

TEST_F(CIteratorBase_test, empty_source_1)
{
    std::string buffer = "";
    auto stream = baseex::core::CreateStreamBuffer(buffer.c_str(), buffer.size());
    auto iterator = CreateBaseIterator(stream, ' ');
    ASSERT_EQ(false, iterator->next());
}

TEST_F(CIteratorBase_test, empty_source_2)
{
    std::string buffer = " ";
    auto stream = baseex::core::CreateStreamBuffer(buffer.c_str(), buffer.size());
    auto iterator = CreateBaseIterator(stream, ' ');
    ASSERT_EQ(true, iterator->next());
    ASSERT_STREQ("", ConvertToString(iterator->current()).c_str());
}
/*
TEST_F(CIteratorBase_test, empty_source_3)
{
std::string buffer = "  ";
auto stream = baseex::core::CreateStreamBuffer(buffer.c_str(), buffer.size());
auto iterator = CreateBaseIterator(stream, ' ');
ASSERT_EQ(false, iterator->next());
}*/
