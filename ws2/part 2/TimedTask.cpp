#include <algorithm>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
#include <cstring>
using namespace std;
using namespace std::chrono_literals;
using namespace std;
#include"TimedTask.h"

namespace sdds {

    TimedTask::TimedTask()
    {
        m_noOfrecords = 0;
    }

    void TimedTask::startClock()
    {
        m_start = std::chrono::steady_clock::now();
    }

    void TimedTask::stopClock()
    {
        m_end = std::chrono::steady_clock::now();
    }

    void TimedTask::addTask(const char* taskName)
    {   
        if( m_noOfrecords < 10 )
        {
            strcpy(m_task[m_noOfrecords].m_taskname, taskName);

            strcpy(m_task[m_noOfrecords].m_unitsoftime, "nanoseconds");

            m_task[m_noOfrecords].m_duration = (m_end - m_start);

            m_noOfrecords+=1;
        }
    }


    ostream& operator<<(ostream& os, const TimedTask& obj)
    {
        //os << dt.mo << '/' << dt.da << '/' << dt.yr;

        os <<"--------------------------\n";
        os <<"Execution Times:\n";
        os <<"--------------------------\n";

        for(int i=0;i< obj.m_noOfrecords;i++)
        {    
            os << left << setw(21) << obj.m_task[i].m_taskname << " ";
            os << right << fixed << setprecision(0) << setw(13) <<obj.m_task[i].m_duration.count();
            os << " " << obj.m_task[i].m_unitsoftime << endl;
        }
        os <<"--------------------------\n";
        return os;
    }


}