#pragma once

#include <parserlog/model/export.hpp>

#include <string>
#include <map>
#include <fstream>
#include <time.h>

namespace parserlog {
namespace model {

class ThreadInfo
{
public:
    ThreadInfo()
        :m_Id(0), m_Count(0)
    {
        memset(&m_TimeStart, 0, sizeof(m_TimeStart));
        memset(&m_TimeEnd, 0, sizeof(m_TimeStart));
    }

    uint64_t m_Id;
    tm m_TimeStart;
    tm m_TimeEnd;
    uint64_t m_Count;
    std::map<std::string, int> m_ComponentCount;
};

}
}
