#pragma once

#include <parserlog/core/export.hpp>
#include <parserlog/model/LineInfo.hpp>

#include <string>

namespace parserlog {
namespace core {

PARSERLOG_CORE_EXPORT bool isLogFormat(const std::string &aString);
PARSERLOG_CORE_EXPORT parserlog::model::LineInfo GetLineInfo(const std::string &aString);

}
}
