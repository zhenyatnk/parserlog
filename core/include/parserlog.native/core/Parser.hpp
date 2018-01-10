#pragma once

#include <parserlog.native/core/export.hpp>
#include <parserlog.native/model/LineInfo.hpp>
#include <parserlog.native/model/ThreadInfo.hpp>

#include <string>
#include <memory>
#include <map>

namespace parserlog {
namespace native {
namespace core {

PARSERLOG_NATIVE_CORE_EXPORT bool isLogFormat(const std::string &aString);
PARSERLOG_NATIVE_CORE_EXPORT parserlog::native::model::LineInfo GetLineInfo(const std::string &aString);
PARSERLOG_NATIVE_CORE_EXPORT  std::map<uint64_t, parserlog::native::model::ThreadInfo> GetThreadsInfo(std::shared_ptr<std::fstream> aFile);

}
}
}
