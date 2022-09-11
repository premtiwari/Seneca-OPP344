#ifndef SDDS_CENTRALUNIT_H
#define SDDS_CENTRALUNIT_H
#define _CRT_SECURE_NO_WARNINGS

#include <string>
#include <iomanip>
#include <cstring>
#include <fstream>
#include <iostream>
#include <stdexcept>
#include <algorithm>
#include "Job.h"

using namespace std;

namespace sdds {

	const size_t MAX_jobs = 4;
	const size_t MAX_processor = 100;

	template <typename T>
	class CentralUnit {

		std::string m_type{};
		T** m_items{}; 
		Job* m_jobs[MAX_jobs]{}; 
		size_t m_size{}; 
		size_t m_count{}; 
	public:
		std::ostream& log = std::cout;
		CentralUnit();
		CentralUnit(std::string, std::string );
		CentralUnit(const CentralUnit&);
		CentralUnit(CentralUnit<T>&&);
		~CentralUnit();
		CentralUnit<T>& operator=(const CentralUnit<T>&&);
		CentralUnit<T>& operator+=(std::string);
		CentralUnit<T>& operator+=(T*);
		size_t get_available_units()const;
		T* operator[](string);
		void display();
		void run();
		bool has_jobs()const;
	};


	template<typename T>
	CentralUnit<T>::CentralUnit()
	{
		m_jobs=nullptr;
		m_items=nullptr;
	}

	template<typename T>
	CentralUnit<T>::CentralUnit(string cu_type, string file_name) {

		ifstream file;
		file.open(file_name);

		if (file.is_open()) {

			m_items = new T *[MAX_processor];
			m_type = cu_type;

			string type;
			string name;
			string capacity;
			char ch;

			while (!file.eof()) {

				file >> type;
				file >> ch;
				file >> name;
				file >> ch;
				file >> capacity;
				size_t work_capacity;
				if(isdigit(capacity[0]) ) work_capacity = std::stoi(capacity);
				else work_capacity = 1;
			
				m_items[m_size] = new T(cu_type, type, name, work_capacity);
				m_size++;
			}

			return;
			
		}

		throw std::invalid_argument("File cannot be opened.");

	}

	template<typename T>
	CentralUnit<T>::CentralUnit(const CentralUnit<T>& cu) {
		throw exception();
	}


	template<typename T>
	sdds::CentralUnit<T>::~CentralUnit() {
		for (size_t i = 0; i < m_size ; i++) delete m_items[i]; 
		delete[] m_items;
	}

	template<typename T>
	T* sdds::CentralUnit<T>::operator[](string job_name)
	{	
		for (size_t i = 0; i < m_size; i++)	
			if(m_items[i]->get_current_job()!=nullptr ) 
				if(!strcmp( m_items[i]->get_current_job()->job_name().c_str() , job_name.c_str())) return m_items[i];
		throw out_of_range("Job is not being handled by a unit.");
	}

	template<typename T>
	void sdds::CentralUnit<T>::display() {
		cout<<"Central Processing Unit list\n";
		for (size_t i = 1; i <= m_size; i++) cout<< "[" << setfill('0') << setw(4) << i << "] "<<*m_items[i-1]<<endl;
	}

	template<typename T>
	CentralUnit<T>::CentralUnit(CentralUnit<T>&& cu) {
		*this=move(cu);
	}

	template<typename T>
	CentralUnit<T>& CentralUnit<T>::operator=(const CentralUnit<T>&& cu) {
		if (this != &cu) {
			for (size_t i = 0; i < m_size ; i++) delete m_items[i]; 
			delete[] m_items;
			m_type = cu.m_type;
			m_items = cu.m_items;
			m_jobs = cu.m_jobs;
			m_size = cu.m_size;
			m_count = cu.m_count;
			cu.m_type = nullptr;
			cu.m_items = nullptr;
			cu.m_jobs = nullptr;
			cu.m_size = nullptr;
			cu.m_count = nullptr;
		}
		return *this;
	}

	template<typename T>
	CentralUnit<T>& CentralUnit<T>::operator+=(T*new_processor)
	{
		m_items[m_size] = new_processor;
		m_size++;
		return *this;
	}

	template<typename T>
	CentralUnit<T>& CentralUnit<T>::operator+=(string job) {

		if (m_count >= MAX_jobs) {
			m_count = 4;
			throw "error";
		}
		else m_jobs[m_count++] = new Job(job);
	
		return *this;
	}

	template<typename T>
	bool CentralUnit<T>::has_jobs()const {
		for (size_t i = 0; i < m_size; i++) if(m_items[i]->get_current_job() != nullptr) return 1;
		return 0;
	}	


	template<typename T>
	size_t CentralUnit<T>::get_available_units()const {
		size_t available_units = 0;
		for (size_t i = 0; i < m_size; i++) if (m_items[i]->get_current_job() == nullptr) available_units++;
		return available_units;
	}	

	template<typename T>
	void sdds::CentralUnit<T>::run() {
		for (size_t i = 0; i < m_size; i++) {
			if (m_count > 0 && m_count <= MAX_jobs) 
				if (!*m_items[i]) *m_items[i] += m_jobs[--m_count];
			
			bool flag=false;
			if( m_items[i]->get_current_job() != nullptr  ) flag=true;
			m_items[i]->run();
			if( m_items[i]->get_current_job() == nullptr && flag ) cout<<get_available_units()<<" units available.\n";
		}
	}

}
#endif // !SDDS_CENTRALUNIT_H
