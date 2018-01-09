#include <parserlog/core/Parser.hpp>

#include <sstream>
#include <iomanip>

namespace parserlog {
namespace core {

bool isLogFormat(const std::string &aString)
{
    std::string threadID = "";
    std::stringstream lStringStream(aString);
    return (!!(std::getline(lStringStream, threadID, '\t')) && !!(std::getline(lStringStream, threadID, '\t')) && threadID.substr(0, 2) == "0x");
}

parserlog::model::LineInfo GetLineInfo(const std::string &aString)
{
    parserlog::model::LineInfo lLineInfo;
    std::stringstream lStringStream(aString);
    auto miliseconds = 0;
    std::string threadID = "";
    lStringStream >> std::get_time(&lLineInfo.m_TimeStamp, "%H:%M:%S.");
    lStringStream >> miliseconds;
    lStringStream >> threadID;
    if(!threadID.empty() && threadID.substr(0, 2) == "0x")
        lLineInfo.m_ThreadId = std::stoul(threadID, nullptr, 16);
    lStringStream >> lLineInfo.m_Type;
    lStringStream >> lLineInfo.m_Component;
    return lLineInfo;
}

}
}