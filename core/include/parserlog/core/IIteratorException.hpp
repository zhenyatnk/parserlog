#pragma once

#include <parserlog/core/export.hpp>
#include <parserlog/core/BaseExceptions.hpp>

namespace parserlog {
namespace core {
namespace exceptions {

class PARSERLOG_CORE_EXPORT iterator_error
    :public parserlog_error_base::error_base
{
public:
    iterator_error(const std::string &aMessage, const int &aErrorCode)
        :parserlog_error_base::error_base("Iterator error: \'" + aMessage + "\'", aErrorCode)
    {}
};

class PARSERLOG_CORE_EXPORT iterator_out_of_range_error
    :public iterator_error
{
public:
    iterator_out_of_range_error(const std::string &aMessage, const int &aErrorCode)
        :iterator_error("Position out of range " + aMessage, aErrorCode)
    {}
};

class PARSERLOG_CORE_EXPORT iterator_invalid_position_error
    :public iterator_error
{
public:
    iterator_invalid_position_error(const std::string &aMessage, const int &aErrorCode)
        :iterator_error("Invalid position " + aMessage, aErrorCode)
    {}
};

}
}
}
