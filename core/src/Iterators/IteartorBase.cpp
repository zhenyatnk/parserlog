#include <parserlog/core/IteratorImpls.hpp>
#include <baseex/core/IIteratorException.hpp>

namespace parserlog {
namespace core {

class CIteratorBase
    :public baseex::core::TIterator<baseex::core::experimental::IStreamBuffer::Ptr>
{
public:
    explicit CIteratorBase(baseex::core::experimental::IStream::Ptr aStream, const char aDelimeter)
        :m_Stream(aStream), m_Delim(aDelimeter), m_StartLine(m_Stream->CreateIterator()), m_EndLine(m_Stream->CreateIterator())
    {}

    virtual void rewind() override
    {
        m_StartLine.rewind();
        m_EndLine.rewind();
    }

    virtual bool is_valid() const override
    {
        return m_StartLine.is_valid();
    }

    virtual bool next() override
    {
        m_StartLine = m_EndLine;
        SkipManyDelimiter(m_StartLine);
        m_EndLine = GetNextLine();
        return is_valid();
    }

    virtual baseex::core::experimental::IStreamBuffer::Ptr current() override
    {
        CHECK_THROW_BOOL(is_valid(), baseex::core::exceptions::iterator_out_of_range_error, "");

        if(m_EndLine.is_valid())
            return m_Stream->Read(m_StartLine, m_EndLine);
        else
            return m_Stream->Read(m_StartLine);
    }

protected:
    baseex::core::experimental::IStream::Iterator GetNextLine()
    {
        auto iterator = m_StartLine;
        while (iterator.next())
            if (iterator.current() == m_Delim)
                break;
        if (iterator.is_valid())
            iterator.prev();
        return iterator;
    }

    void SkipManyDelimiter(baseex::core::experimental::IStream::Iterator &iterator)
    {
        while (iterator.next() && iterator.current() == m_Delim);
    }


private:
    baseex::core::experimental::IStream::Ptr m_Stream;
    const char m_Delim;
    baseex::core::experimental::IStream::Iterator m_StartLine;
    baseex::core::experimental::IStream::Iterator m_EndLine;
};

baseex::core::TIterator<baseex::core::experimental::IStreamBuffer::Ptr>::Ptr CreateBaseIterator(baseex::core::experimental::IStream::Ptr aStream, const char aDelimeter)
{
    return baseex::core::TIterator<baseex::core::experimental::IStreamBuffer::Ptr>::Ptr(new CIteratorBase(aStream, aDelimeter));
}

baseex::core::TIterator<baseex::core::experimental::IStreamBuffer::Ptr>::Ptr CreateIteratorLines(baseex::core::experimental::IStream::Ptr aStream)
{
    return baseex::core::TIterator<baseex::core::experimental::IStreamBuffer::Ptr>::Ptr(new CIteratorBase(aStream, '\n'));
}

baseex::core::TIterator<baseex::core::experimental::IStreamBuffer::Ptr>::Ptr CreateIteratorElements(baseex::core::experimental::IStream::Ptr aStream)
{
    return baseex::core::TIterator<baseex::core::experimental::IStreamBuffer::Ptr>::Ptr(new CIteratorBase(aStream, '\t'));
}

}
}