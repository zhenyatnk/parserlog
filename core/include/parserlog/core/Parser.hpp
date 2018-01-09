#pragma once

#include <parserlog/core/export.hpp>
#include <parserlog/model/LineInfo.hpp>
#include <parserlog/model/ThreadInfo.hpp>

#include <string>
#include <memory>
#include <map>

namespace parserlog {
namespace core {

PARSERLOG_CORE_EXPORT bool isLogFormat(const std::string &aString);
PARSERLOG_CORE_EXPORT parserlog::model::LineInfo GetLineInfo(const std::string &aString);
PARSERLOG_CORE_EXPORT  std::map<uint64_t, parserlog::model::ThreadInfo> GetThreadsInfo(std::shared_ptr<std::fstream> aFile);

}
}
