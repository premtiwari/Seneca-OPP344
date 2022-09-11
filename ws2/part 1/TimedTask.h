#ifndef SDDS_TIMETASK_H
#define SDDS_TIMETASK_H
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <ctime>
#include <chrono>
using namespace std;
using namespace std::chrono_literals;
 
struct Task
{
    char m_taskname[100];
    char m_unitsoftime[20];
    std::chrono::duration<double, std::nano> m_duration;
};



namespace sdds {
    
	class TimedTask {

		int m_noOfrecords{0};

        std::chrono::time_point<std::chrono::steady_clock> m_start;
        std::chrono::time_point<std::chrono::steady_clock> m_end;

        struct Task m_task[10];

        public:

        TimedTask();

        void startClock();

        void stopClock();

        void addTask(const char*);

        friend ostream& operator<<(ostream& os, const TimedTask& obj);


	};
    
}

#endif