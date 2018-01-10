#pragma once

#include <parserlog.native/core/export.hpp>

#include <baseex/core/BaseExceptions.hpp>

namespace parserlog {
namespace native {
namespace core {
namespace exceptions {

class PARSERLOG_NATIVE_CORE_EXPORT parserlog_error_base
    :public baseex::core::exceptions_base::error_base
{
public:
    parserlog_error_base(const std::string &aMessage, const int &aErrorCode)
        :baseex::core::exceptions_base::error_base(aMessage, aErrorCode)
    {}
};

}
}
}
}
