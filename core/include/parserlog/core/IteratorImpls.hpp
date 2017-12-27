#pragma once

#include <parserlog/core/export.hpp>

#include <baseex/core/IIterator.hpp>
#include <baseex/core/IIteratorException.hpp>
#include <baseex/core/IStream.hpp>

#include <string>

namespace parserlog {
namespace core {

PARSERLOG_CORE_EXPORT baseex::core::TIterator<baseex::core::ILinearStream::Ptr>::Ptr CreateBaseIterator(baseex::core::IStream::Ptr, const char aDelimeter);
//PARSERLOG_CORE_EXPORT baseex::core::TIterator<baseex::core::ILinearStream::Ptr>::Ptr CreateBaseIterator(baseex::core::ILinearStream::Ptr, baseex::core::ILinearStream::Ptr delim);
//TIterator<std::string>::Ptr CreateIteratorLines(baseex::core::IStream::Ptr);
//TIterator<std::string>::Ptr CreateIteratorElements(baseex::core::IStream::Ptr);

}
}