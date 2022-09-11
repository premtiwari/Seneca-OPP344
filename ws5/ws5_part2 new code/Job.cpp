#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
#include "Job.h"
#include <iomanip>
using namespace std;

namespace sdds {
	

	Job::Job() 
	{	
		m_title = "";
		Job_Active = false;
	}

	Job::Job(string Title) 
	{
		m_title = Title;
		m_totalWork = (Title.length() % 10) + 1;
		m_remainWork = m_totalWork;
		Job_Active = true;
	}


	bool Job::is_active() 
	{
		return Job_Active;
	}

	bool Job::is_complete() 
	{
		return m_remainWork == 0;
	}

	string Job::job_name() 
	{
		return m_title;
	}

	void Job::display(ostream& ostr) 
	{
		ostr << "`" << m_title << "` [" << std::setfill('0') << std::setw(2) << m_remainWork << "/" << std::setfill('0') << std::setw(2) << m_totalWork << " remaining]";
	}

	void Job::operator()(size_t& workUnit) 
	{

		if (workUnit > m_totalWork) {
			m_remainWork = 0;
			throw std::underflow_error("underflow error");
		}
		else
		{
			m_remainWork = m_remainWork - workUnit;
			if (m_remainWork <= 0) m_remainWork = 0;
		}

	}

	ostream& operator<<(ostream& ostr, Job& J) 
	{
		J.display(ostr);
		return ostr;
	}

}