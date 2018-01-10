#pragma once

#include <parserlog.native/model/export.hpp>

#include <string>
#include <map>
#include <fstream>
#include <time.h>

namespace parserlog {
namespace native {
namespace model {

class LineInfo
{
public:
    LineInfo()
        :m_ThreadId(0)
    {
        memset(&m_TimeStamp, 0, sizeof(m_TimeStamp));
    }

    tm m_TimeStamp;
    uint64_t m_ThreadId;
    std::string m_Type;
    std::string m_Component;
};

}
}
}
