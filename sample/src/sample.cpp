#include <parserlog/core/export.hpp>
#include <baseex/core/CFileName.hpp>
#include <baseex/core/Unicode.hpp>
#include <baseex/core/RAII.hpp>

#include <stdio.h>
#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include <ctime>

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

std::string getline(const char *buff, uint64_t size, uint64_t& offset)
{
    auto start = offset;
    auto end = offset;
    while (end < size)
    {
        if (buff[end] == '\n')
        {
            offset = end + 1;
            return std::string(buff + start, end - start);
        }
        ++end;
    }
    offset = end;
    return std::string(buff + start, end - start);
}

int main(int ac, char** av)
{
    if (ac > 1)
    {
        {
            CTimeLoger time_log("Read std::fstream");
            std::fstream file;
            file.open(av[1], std::fstream::in);
            std::string l;
            uint64_t lCount = 0;
            while (std::getline(file, l))
                ++lCount;
            std::cout << lCount << std::endl;
            file.close();
        }

        {
            uint64_t chunck_size = 1024 * 1024 * 15;
            CTimeLoger time_log("Read with cache std::fstream");
            std::fstream file;
            file.open(av[1], std::fstream::in);
            file.seekg(0, file.end);
            auto size_file = file.tellg();
            file.seekg(0, file.beg);
            std::streampos lReading = 0;
            while (lReading < size_file)
            {

                std::streampos read = chunck_size;
                if (chunck_size < size_file)
                    read = size_file;

                char *read_buffer = new char[read];
                file.read(read_buffer, read);
                lReading += read;
                
                uint64_t offset = 0;
                while (offset < read)
                {
                    auto l = getline(read_buffer, read, offset);
                }
                delete [] read_buffer;
            }
        }

    }
    
    return 0;
}