#pragma once

#include <parserlog/core/IIterator.hpp>
#include <parserlog/core/IIteratorException.hpp>

#include <baseex/core/IStream.hpp>

#include <string>

namespace parserlog {
namespace core {

PARSERLOG_CORE_EXPORT TIterator<char>::Ptr CreateIteratorSymbols(baseex::core::IStream::Ptr);
//TIterator<std::string>::Ptr CreateIteratorLines(baseex::core::IStream::Ptr);
//TIterator<std::string>::Ptr CreateIteratorElements(baseex::core::IStream::Ptr);

}
}