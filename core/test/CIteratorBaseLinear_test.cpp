#include <gtest/gtest.h>
#include <parserlog/core/IteratorImpls.hpp>
#include <future>

//--------------------------------------------------------------------------------------------------------------------------------------
using namespace parserlog::core;

class CIteratorBaseLinear_test
    :public ::testing::Test
{
public:
    void SetUp()
    {}
};

TEST_F(CIteratorBaseLinear_test, empty_source)
{
}