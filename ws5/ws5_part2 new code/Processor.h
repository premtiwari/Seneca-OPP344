#ifndef SDDS_PROCESSOR_H
#define SDDS_PROCESSOR_H

#include <string>
#include "Job.h"
#include "CentralUnit.h"

namespace sdds {
	class Processor {
		string m_host{};
		string m_brand{};
		string m_code{};
		size_t m_power{}; 
		Job* m_current{}; 

	public:
		Processor(string, string , string , size_t );
		Processor(CentralUnit<Processor> *, string , string , size_t ) ;
		void run();
		void display(ostream& ostr = cout);
		explicit operator bool() const;
		Processor& operator+=(Job*&);
		Job* get_current_job() const;
		bool become_empty();

	};
	ostream& operator<<(ostream&,  Processor&);
}
#endif // !SDDS_PROCESSOR_H