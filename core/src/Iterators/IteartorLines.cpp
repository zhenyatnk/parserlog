#include <parserlog.native/core/IteratorImpls.hpp>
#include <baseex/core/IIteratorException.hpp>

namespace parserlog {
namespace native {
namespace core {

class CIteratorLines
    :public baseex::core::TIterator<std::string>
{
public:
    explicit CIteratorLines(std::shared_ptr<std::fstream> aFile)
        :m_File(aFile), m_IsValid(false), m_Current("")
    {}

    virtual void rewind() override
    {
        m_Current = "";
        m_IsValid = false;
        m_File->seekg(0, m_File->beg);
    }

    virtual bool is_valid() const override
    {
        return m_IsValid;
    }

    virtual bool next() override
    {
        return m_IsValid = !!(std::getline(*m_File, m_Current));
    }

    virtual std::string current() override
    {
        CHECK_THROW_BOOL(is_valid(), baseex::core::exceptions::iterator_out_of_range_error, "");
        return m_Current;
    }

private:
    std::shared_ptr<std::fstream> m_File;
    bool m_IsValid;
    std::string m_Current;
};

baseex::core::TIterator<std::string>::Ptr CreateIteratorLines(std::shared_ptr<std::fstream> aFile)
{
    return baseex::core::TIterator<std::string>::Ptr(new CIteratorLines(aFile));
}

}
}
}