#include <parserlog/core/IteratorImpls.hpp>
#include <baseex/core/IIteratorException.hpp>

#include <sstream>

namespace parserlog {
namespace core {

class CIteratorTabs
    :public baseex::core::TIterator<std::string>
{
public:
    explicit CIteratorTabs(const std::string &aSrting)
        :m_Stream(aSrting), m_IsValid(false)
    {}

    virtual void rewind() override
    {
        m_Current = "";
        m_IsValid = false;
        m_Stream.seekg(0, m_Stream.beg);
    }

    virtual bool is_valid() const override
    {
        return m_IsValid;
    }

    virtual bool next() override
    {
        return m_IsValid = !!(std::getline(m_Stream, m_Current, '\t'));
    }

    virtual std::string current() override
    {
        CHECK_THROW_BOOL(is_valid(), baseex::core::exceptions::iterator_out_of_range_error, "");
        return m_Current;
    }

private:
    std::stringstream m_Stream;
    bool m_IsValid;
    std::string m_Current;
};

baseex::core::TIterator<std::string>::Ptr CreateIteratorTabs(const std::string &aSrting)
{
    return baseex::core::TIterator<std::string>::Ptr(new CIteratorTabs(aSrting));
}

}
}