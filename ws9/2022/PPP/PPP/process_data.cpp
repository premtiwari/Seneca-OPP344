#include "process_data.h"
#include <thread>
#include <mutex>

using namespace std;

namespace sdds_ws9
{

	static mutex key;

	void computeAvgFactor(const int *arr_var, int size_var, int divisor_var, double &avg_var)
	{

		avg_var = 0;

		int i = 0;
		while (i < size_var)
		{
			
			avg_var += arr_var[i];

			i++;
		}

		avg_var /= divisor_var;
	}

	void computeVarFactor(const int *arr_var, int size_var, int divisor_var, double avg_var, double &var)
	{
		var = 0;

		int i = 0;

		while (i < size_var)
		{

			var += (arr_var[i] - avg_var) * (arr_var[i] - avg_var);

			i++;
		}

		var /= divisor_var;
	}
	ProcessData::operator bool() const
	{

		return total_items > 0 && data && num_threads > 0 && averages && variances && p_indices;
	}

	ProcessData::ProcessData(string filename_var, int n_threads_var)
	{

		fstream file(filename_var,
					 ios::in | ios::binary);

		if (!file)
		{
			cout << "File cannot be opened.";
		}

		file.read(reinterpret_cast<char *>(&total_items), sizeof(total_items));

		data = new int[total_items];

		// declare variable
		int i = 0;
		while (!file.eof())
		{

			file.read(reinterpret_cast<char *>(&data[i]), sizeof(data[i]));
			i++;
		}

		cout << "Item's count in file '" << filename_var << "': " << total_items << endl;
		cout << "  [" << data[0] << ", " << data[1] << ", " << data[2] << ", ... , "
			 << data[total_items - 3] << ", " << data[total_items - 2] << ", "
			 << data[total_items - 1] << "]\n";

		num_threads = n_threads_var;
		averages = new double[num_threads]{};
		variances = new double[num_threads]{};
		p_indices = new int[num_threads + 1]{};

		int k = 0;
		while (k < num_threads + 1)
		{
			p_indices[k] = k * (total_items / num_threads);
			k++;
		}
	}
	ProcessData::~ProcessData()
	{
		// delete the data
		delete[] data;

		// delete the averages
		delete[] averages;

		// delete the variances
		delete[] variances;

		// delete the p_indices
		delete[] p_indices;
	}

	int ProcessData::operator()(string fileName_var, double &avg_var, double &var)
	{

		vector<thread> var_threads;
		vector<thread> avg_threads;

		int i = 0;
		while (i < num_threads)
		{
			auto average = bind(computeAvgFactor, &data[p_indices[i]], total_items / num_threads, total_items, ref(averages[i]));

			avg_threads.push_back(thread(average));

			i++;
		}

		int j = 0;

		while (j < num_threads)
		{
			avg_threads[j].join();
			j++;
		}

		int k = 0;
		while (k < num_threads)
		{

			avg_var += averages[k];
			k++;
		}

		int m = 0;

		while (m < num_threads)
		{

			auto variance = bind(computeVarFactor, &data[p_indices[m]], total_items / num_threads, total_items, avg_var,
								 ref(variances[m]));

			var_threads.push_back(thread(variance));

			m++;
		}

		int x = 0;
		while (x < num_threads)
		{
			var_threads[x].join();
			x++;
		}

		int h = 0;
		while (h < num_threads)
		{
			var += variances[h];
			h++;
		}

		fstream file(fileName_var,
					 ios::out | ios::binary);
		file.write(reinterpret_cast<char *>(&total_items), sizeof(total_items));

		for (int l = 0; l < total_items; l++)
		{
			file.write(reinterpret_cast<char *>(&data[l]), sizeof(data[l]));
		}

		return 0;
	}
}