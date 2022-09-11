#include <iostream>
#include "Processor.h"
#include <exception>

using namespace std;
namespace sdds {

	Processor::Processor(string address, string brand, string code, size_t power)  
	{
		m_host=address;
		m_brand=brand;
		m_code=code; 
		m_power=power;
		m_current=nullptr;
	}

	Processor::Processor(CentralUnit<sdds::Processor> *cpu , string brand, string code, size_t power) 
	{
		m_host = "Process";
		m_brand=brand;
		m_code=code; 
		m_power=power;
		m_current=nullptr;
	}	

	void Processor::run() 
	{
	
		if( m_current!=nullptr)
		try {
			if(m_current->is_complete()) 
			{	
				cout<< "[COMPLETE] " << *m_current << " using ("<< m_power<<") "<<m_brand <<" "<<m_code<<endl;
				delete m_current;
				m_current = nullptr;
			}
			else 
			{
				Job &j=*m_current;
				j(m_power);
				if(m_current->is_complete()) 
				{	
					cout<< "[COMPLETE] " << *m_current << " using ("<< m_power<<") "<<m_brand <<" "<<m_code<<endl;
					delete m_current;
					m_current = nullptr;
				}
			}

		}
		catch (const exception& e) 
		{
			cout << "Failed to complete job "<< m_current->job_name() << endl;
			delete m_current;
			m_current = nullptr;
		}
	}


	Processor::operator bool() const 
	{
		if(m_current == nullptr) return false;
		return true;
	}

	Processor& Processor::operator+=(Job*& job) 
	{
		if( m_current == nullptr)
			m_current = job;
		else 
			throw;
		return *this;
	}

	Job* Processor::get_current_job() const 
	{
		return m_current;
	}

	void Processor::display(std::ostream& ostr)
	{
		ostr << "(" << m_power <<") " << m_brand <<" "<<m_code;
		if(m_current != nullptr ) ostr <<" processing "<< *m_current;
	}

	std::ostream& operator<<(std::ostream& out,Processor& processor){
		processor.display(out);
		return out;
	}

}