#include <parserlog/core/export.hpp>
#include <parserlog/core/IteratorImpls.hpp>
#include <parserlog/core/Parser.hpp>
#include <parserlog/model/ThreadInfo.hpp>
#include <parserlog/model/LineInfo.hpp>

#include <baseex/core/CFileName.hpp>
#include <baseex/core/IStream.hpp>
#include <baseex/core/Unicode.hpp>
#include <baseex/core/RAII.hpp>

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <chrono>
#include <ctime>
#include <iomanip>
#include <map>

class CTimeLoger
    :public baseex::core::IRAII
{
public:
    CTimeLoger(const std::string &aPrefix = "")
        :m_Start(std::chrono::system_clock::now()), m_Prefix(aPrefix)
    {
        auto begin = std::chrono::system_clock::to_time_t(m_Start);
        std::cout << m_Prefix << ":Start " << std::ctime(&begin) << std::endl;
    }

    ~CTimeLoger()
    {
        auto end = std::chrono::system_clock::now();
        auto end_time = std::chrono::system_clock::to_time_t(end);
        std::cout << m_Prefix << ":Finish " << std::ctime(&end_time) << std::endl;
        std::cout << m_Prefix << ":Elapsed " << std::chrono::duration_cast<std::chrono::milliseconds>(end - m_Start).count() << " ms." <<std::endl;
    }

private:
    std::chrono::time_point<std::chrono::system_clock> m_Start;
    std::string m_Prefix;
};

int main(int ac, char** av)
{
    if (ac > 1)
    {
        {
            CTimeLoger time_log("Read iterators getline");
            auto file = std::make_shared<std::fstream>();
            file->open(av[1], std::fstream::in);
            uint64_t lCount = 0;
            std::map<uint64_t, parserlog::model::ThreadInfo> lThreads;
            auto iterator = parserlog::core::CreateIteratorLines(file);
            while (iterator->next())
            {
                auto line = iterator->current();
                if (parserlog::core::isLogFormat(line))
                {
                    auto info = parserlog::core::GetLineInfo(line);
                    auto thread = lThreads.find(info.m_ThreadId);
                    if (thread == lThreads.end())
                    {
                        parserlog::model::ThreadInfo thread;
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

            std::cout << lCount << std::endl;
            file->close();
        }


    }



    return 0;
}
