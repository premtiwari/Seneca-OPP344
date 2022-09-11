#ifndef SDDS_W9_PROCESSDATA_H
#define SDDS_W9_PROCESSDATA_H

#include<fstream>
#include<thread>
#include<mutex>

#include<iostream>
#include<string>

#include<vector>
#include<functional>

using namespace std;



namespace sdds_ws9 {

	void computeVarFactor(const int*, int, int, double, double&);
	void computeAvgFactor(const int*, int, int, double&);
	
	
	class ProcessData {

		double *variances{nullptr}; // to hold variance factors
		
		int total_items{};
		
		int num_threads{ 0 }; // to hold number of threads
		
		int *data{};
		
		int *p_indices{nullptr};	 // to hold partitioning indices
		double* averages{ nullptr }; // to hold average factors 
		
		
	public:
		operator bool() const;
		int operator()(string, double &, double &);
		
		
		
		ProcessData& operator=(const ProcessData&) = delete;
		~ProcessData();

		ProcessData(string,int);
		ProcessData(const ProcessData &) = delete;
	};


}



#endif 