#pragma once

#include <parserlog/core/export.hpp>

#include <baseex/core/IIterator.hpp>
#include <baseex/core/IIteratorException.hpp>
#include <baseex/core/IStream.hpp>

#include <string>
#include <fstream>

namespace parserlog {
namespace core {

PARSERLOG_CORE_EXPORT baseex::core::TIterator<std::string>::Ptr CreateIteratorLines(std::shared_ptr<std::fstream> aFile);

}
}
