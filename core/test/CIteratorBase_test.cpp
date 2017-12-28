#include <gtest/gtest.h>
#include <parserlog/core/IteratorImpls.hpp>
#include <future>

//--------------------------------------------------------------------------------------------------------------------------------------
using namespace parserlog::core;
using namespace baseex::core::experimental;

namespace
{
std::string ConvertToString(IStream::Ptr aStream)
{
    uint8_t *lBuffer = new uint8_t[aStream->Size()];
    aStream->Read(0, lBuffer, aStream->Size());
    std::string lRet((char*)lBuffer, aStream->Size());
    delete[] lBuffer;
    return lRet;
}
std::string ConvertToString(IStreamBuffer::Ptr aStream)
{
    return std::string((const char*)aStream->GetData(), aStream->Size());
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
    auto stream = CreateStreamBuffer(buffer.c_str(), buffer.size());
    auto iterator = CreateBaseIterator(stream, ' ');
    ASSERT_EQ(false, iterator->next());
}

TEST_F(CIteratorBase_test, empty_source_2)
{
    std::string buffer = " ";
    auto stream = CreateStreamBuffer(buffer.c_str(), buffer.size());
    auto iterator = CreateBaseIterator(stream, ' ');
    ASSERT_EQ(false, iterator->next());
}

TEST_F(CIteratorBase_test, empty_source_3)
{
    std::string buffer = "  ";
    auto stream = CreateStreamBuffer(buffer.c_str(), buffer.size());
    auto iterator = CreateBaseIterator(stream, ' ');
    ASSERT_EQ(false, iterator->next());
}


TEST_F(CIteratorBase_test, start_delims)
{
    std::string buffer = "  a";
    auto stream = CreateStreamBuffer(buffer.c_str(), buffer.size());
    auto iterator = CreateBaseIterator(stream, ' ');
    ASSERT_EQ(true, iterator->next());
    ASSERT_STREQ("a", ConvertToString(iterator->current()).c_str());
}

TEST_F(CIteratorBase_test, start_delims_2)
{
    std::string buffer = "  a  s";
    auto stream = CreateStreamBuffer(buffer.c_str(), buffer.size());
    auto iterator = CreateBaseIterator(stream, ' ');
    ASSERT_EQ(true, iterator->next());
    ASSERT_EQ(true, iterator->next());
    ASSERT_STREQ("s", ConvertToString(iterator->current()).c_str());
}

TEST_F(CIteratorBase_test, start_delims_3)
{
    std::string buffer = "  a  s";
    auto stream = CreateStreamBuffer(buffer.c_str(), buffer.size());
    auto iterator = CreateBaseIterator(stream, ' ');
    ASSERT_EQ(true, iterator->next());
    ASSERT_EQ(true, iterator->next());
    ASSERT_EQ(false, iterator->next());
}

TEST_F(CIteratorBase_test, end_delims_3)
{
    std::string buffer = "  a  s  ";
    auto stream = CreateStreamBuffer(buffer.c_str(), buffer.size());
    auto iterator = CreateBaseIterator(stream, ' ');
    ASSERT_EQ(true, iterator->next());
    ASSERT_EQ(true, iterator->next());
    ASSERT_EQ(false, iterator->next());
}

TEST_F(CIteratorBase_test, one_symbol)
{
    std::string buffer = "a";
    auto stream = CreateStreamBuffer(buffer.c_str(), buffer.size());
    auto iterator = CreateBaseIterator(stream, ' ');
    ASSERT_EQ(true, iterator->next());
    ASSERT_STREQ("a", ConvertToString(iterator->current()).c_str());
    ASSERT_EQ(false, iterator->next());
}

TEST_F(CIteratorBase_test, many_symbols_1)
{
    std::string buffer = "asb";
    auto stream = CreateStreamBuffer(buffer.c_str(), buffer.size());
    auto iterator = CreateBaseIterator(stream, ' ');
    ASSERT_EQ(true, iterator->next());
    ASSERT_STREQ("asb", ConvertToString(iterator->current()).c_str());
    ASSERT_EQ(false, iterator->next());
}

TEST_F(CIteratorBase_test, start_delim_many_symbols)
{
    std::string buffer = "   asb";
    auto stream = CreateStreamBuffer(buffer.c_str(), buffer.size());
    auto iterator = CreateBaseIterator(stream, ' ');
    ASSERT_EQ(true, iterator->next());
    ASSERT_STREQ("asb", ConvertToString(iterator->current()).c_str());
    ASSERT_EQ(false, iterator->next());
}

TEST_F(CIteratorBase_test, start_end_delim_many_symbols)
{
    std::string buffer = "   asb   ";
    auto stream = CreateStreamBuffer(buffer.c_str(), buffer.size());
    auto iterator = CreateBaseIterator(stream, ' ');
    ASSERT_EQ(true, iterator->next());
    ASSERT_STREQ("asb", ConvertToString(iterator->current()).c_str());
    ASSERT_EQ(false, iterator->next());
}

TEST_F(CIteratorBase_test, start_delim_many_symbols_1)
{
    std::string buffer = "   asb   asddw s";
    auto stream = CreateStreamBuffer(buffer.c_str(), buffer.size());
    auto iterator = CreateBaseIterator(stream, ' ');
    ASSERT_EQ(true, iterator->next());
    ASSERT_EQ(true, iterator->next());
    ASSERT_EQ(true, iterator->next());
    ASSERT_STREQ("s", ConvertToString(iterator->current()).c_str());
    ASSERT_EQ(false, iterator->next());
}

TEST_F(CIteratorBase_test, start_end_delim_many_symbols_1)
{
    std::string buffer = "   asb   asddw s ";
    auto stream = CreateStreamBuffer(buffer.c_str(), buffer.size());
    auto iterator = CreateBaseIterator(stream, ' ');
    ASSERT_EQ(true, iterator->next());
    ASSERT_EQ(true, iterator->next());
    ASSERT_EQ(true, iterator->next());
    ASSERT_STREQ("s", ConvertToString(iterator->current()).c_str());
    ASSERT_EQ(false, iterator->next());
}
