#include <parserlog.native/core/Parser.hpp>
#include <parserlog.native/core/IteratorImpls.hpp>

#include <sstream>
#include <iomanip>

namespace parserlog {
namespace native {
namespace core {

bool isLogFormat(const std::string &aString)
{
    std::string threadID = "";
    std::stringstream lStringStream(aString);
    return (!!(std::getline(lStringStream, threadID, '\t')) && !!(std::getline(lStringStream, threadID, '\t')) && threadID.substr(0, 2) == "0x");
}

parserlog::native::model::LineInfo GetLineInfo(const std::string &aString)
{
    parserlog::native::model::LineInfo lLineInfo;
    std::stringstream lStringStream(aString);
    auto miliseconds = 0;
    std::string threadID = "";
    lStringStream >> std::get_time(&lLineInfo.m_TimeStamp, "%H:%M:%S.");
    lStringStream >> miliseconds;
    lStringStream >> threadID;
    if (!threadID.empty() && threadID.substr(0, 2) == "0x")
        lLineInfo.m_ThreadId = std::stoul(threadID, nullptr, 16);
    lStringStream >> lLineInfo.m_Type;
    lStringStream >> lLineInfo.m_Component;
    return lLineInfo;
}


std::map<uint64_t, parserlog::native::model::ThreadInfo> GetThreadsInfo(std::shared_ptr<std::fstream> aFile)
{
    std::map<uint64_t, parserlog::native::model::ThreadInfo> lThreads;
    auto iterator = CreateIteratorLines(aFile);
    while (iterator->next())
    {
        auto line = iterator->current();
        if (isLogFormat(line))
        {
            auto info = GetLineInfo(line);
            auto thread = lThreads.find(info.m_ThreadId);
            if (thread == lThreads.end())
            {
                parserlog::native::model::ThreadInfo thread;
                thread.m_Id = info.m_ThreadId;
                thread.m_Count = 1;
                thread.m_TimeStart = info.m_TimeStamp;
                thread.m_ComponentCount[info.m_Component] = 1;

                lThreads[info.m_ThreadId] = thread;
            }
            else
            {
                ++thread->second.m_Count;
                thread->second.m_TimeEnd = info.m_TimeStamp;

                auto component = thread->second.m_ComponentCount.find(info.m_Component);
                if (component == thread->second.m_ComponentCount.end())
                    thread->second.m_ComponentCount[info.m_Component] = 1;
                else
                    ++component->second;

            }

        }
    }
    return lThreads;
}

}
}
}