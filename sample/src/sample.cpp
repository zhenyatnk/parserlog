#include <parserlog.native/core/export.hpp>
#include <parserlog.native/core/IteratorImpls.hpp>
#include <parserlog.native/core/Parser.hpp>
#include <parserlog.native/model/ThreadInfo.hpp>
#include <parserlog.native/model/LineInfo.hpp>

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

int main(int ac, char** av)
{
    if (ac > 1)
    {
        {
            auto file = std::make_shared<std::fstream>();
            file->open(av[1], std::fstream::in);

            std::chrono::time_point<std::chrono::system_clock> start(std::chrono::system_clock::now());
            baseex::core::dtor_raii l([&start]() { std::cout << "Elapsed " << std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now() - start).count() << " ms." << std::endl; });
            if (file->is_open())
            {
                baseex::core::dtor_raii l([file]() { file->close(); });
                std::map<uint64_t, parserlog::native::model::ThreadInfo> lThreads = parserlog::native::core::GetThreadsInfo(file);
            }
        }
    }
    return 0;
}
