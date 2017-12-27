#include <parserlog/core/IteratorImpls.hpp>
#include <baseex/core/IIteratorException.hpp>

namespace parserlog {
namespace core {

class CIteratorBase
    :public baseex::core::TIterator<baseex::core::ILinearStream::Ptr>
{
public:
    explicit CIteratorBase(baseex::core::IStream::Ptr aStream, const char aDelimeter)
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

    virtual baseex::core::ILinearStream::Ptr current() override
    {
        CHECK_THROW_BOOL(is_valid(), baseex::core::exceptions::iterator_out_of_range_error, "");

        if(m_EndLine.is_valid())
            return baseex::core::CreateLinearBuffer(m_Stream->Read(m_StartLine, m_EndLine));
        else
            return baseex::core::CreateLinearBuffer(m_Stream->Read(m_StartLine));
    }

protected:
    baseex::core::IStream::Iterator GetNextLine()
    {
        auto iterator = m_StartLine;
        while (iterator.next())
            if (iterator.current() == m_Delim)
                break;
        if (iterator.is_valid())
            iterator.prev();
        return iterator;
    }

    void SkipManyDelimiter(baseex::core::IStream::Iterator &iterator)
    {
        while (iterator.next() && iterator.current() == m_Delim);
    }


private:
    baseex::core::IStream::Ptr m_Stream;
    const char m_Delim;
    baseex::core::IStream::Iterator m_StartLine;
    baseex::core::IStream::Iterator m_EndLine;
};

baseex::core::TIterator<baseex::core::ILinearStream::Ptr>::Ptr CreateBaseIterator(baseex::core::IStream::Ptr aStream, const char aDelimeter)
{
    return baseex::core::TIterator<baseex::core::ILinearStream::Ptr>::Ptr(new CIteratorBase(aStream, aDelimeter));
}

}
}