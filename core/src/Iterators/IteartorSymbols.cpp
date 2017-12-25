#include <parserlog/core/IteratorImpls.hpp>
#include <parserlog/core/IIteratorException.hpp>

namespace parserlog {
namespace core {

template <typename T>
class CIteratorSymbols
    :public TIterator<T>
{
public:
    explicit CIteratorSymbols(baseex::core::IStream::Ptr aStream)
        :m_Stream(aStream), m_Offset(-1), m_Size(aStream->Size())
    {}

    virtual void rewind() override
    {
        m_Offset = -1;
    }

    virtual bool next() override
    {
        m_Offset += sizeof(T);
        return IsExistByIndex(m_Offset);
    }

    virtual T current() override
    {
        CHECK_THROW_BOOL(m_Offset >= 0, exceptions::iterator_invalid_position_error, "");
        CHECK_THROW_BOOL(IsExistByIndex(m_Offset), exceptions::iterator_out_of_range_error, "");

        T value;
        m_Stream->Read(m_Offset, (uint8_t*)(&value), sizeof(T));
        return value;
    }

protected:

    bool IsExistByIndex(int aIndex)
    {
        return aIndex < m_Size;
    }

private:
    baseex::core::IStream::Ptr m_Stream;
    int m_Offset;
    size_t m_Size;
};

TIterator<char>::Ptr CreateIteratorSymbols(baseex::core::IStream::Ptr aStream)
{
    return TIterator<char>::Ptr(new CIteratorSymbols<char>(aStream));
}

}
}