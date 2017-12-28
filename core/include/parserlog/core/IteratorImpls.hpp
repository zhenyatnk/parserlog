#pragma once

#include <parserlog/core/export.hpp>

#include <baseex/core/IIterator.hpp>
#include <baseex/core/IIteratorException.hpp>
#include <baseex/core/IStream.hpp>

#include <string>
#include <fstream>

namespace parserlog {
namespace core {

PARSERLOG_CORE_EXPORT baseex::core::TIterator<baseex::core::experimental::IStreamBuffer::Ptr>::Ptr CreateBaseIterator(baseex::core::experimental::IStream::Ptr, const char aDelimeter);
PARSERLOG_CORE_EXPORT baseex::core::TIterator<baseex::core::experimental::IStreamBuffer::Ptr>::Ptr CreateIteratorLines(baseex::core::experimental::IStream::Ptr);
PARSERLOG_CORE_EXPORT baseex::core::TIterator<baseex::core::experimental::IStreamBuffer::Ptr>::Ptr CreateIteratorElements(baseex::core::experimental::IStream::Ptr);

}
}