#ifndef SDDS_JOB_H
#define SDDS_JOB_H

#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

namespace sdds {
	class Job {

		string m_title;
		size_t m_totalWork{};
		size_t m_remainWork{};
		bool Job_Active{};

	public:
		Job();
		Job(string);
		bool is_active();
		bool is_complete();
		string job_name();
		void display(std::ostream& ostr = std::cout);
		void operator()(size_t&);
	};
	std::ostream& operator<<(std::ostream&, Job&);
}
#endif // !SDDS_JOB_Hd