#ifndef SDDS_GENERATINGLIST_H
#define SDDS_GENERATINGLIST_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <memory>
#include <utility>
#include <fstream>

namespace sdds {
	template<typename T>
	class GeneratingList {

		std::vector<T> list;
	public:

		GeneratingList(){}
		GeneratingList(const char* f) {
			std::ifstream file(f);
			if (!file)
				throw std::string("*** Failed to open file ") + std::string(f) + std::string(" ***");

			while (file) {
				T t;
				if (t.load(file))
					list.push_back(T(t));
			}
		}

		size_t size() const { return list.size(); }
		const T& operator[](size_t i) const { return list[i]; }

		//TODO: Implement the Luhn Algorithm to check the 
		//      valadity of SIN No's
        bool checkLuhn(const std::string& card)
        {
            int digits = card.length();
        
            int sum = 0;
			
			bool isSec = false;

            for (int i = digits - 1; i >= 0; --i) {
        
                int di = card[i] - '0';
        
                if (isSec == true)
                    di = di * 2;
        
                sum += di / 10;
                sum += di % 10;
        
                isSec = !isSec;
            }

            return (sum % 10 == 0);
        }


		//TODO: Overload the += operator with a smart pointer
		// as a second operand.
        void operator+=(const  std::shared_ptr<T> emp)
        {
            list.push_back(*emp);
        }		

		//TODO: Overload the += operator with a raw pointer
		// as a second operand.
        void operator+=(const T& emp)
        {
            list.push_back(emp);
        }

		void print(std::ostream& os) const {
			os << std::fixed << std::setprecision(2);
			for (auto& e : list)
				e.print(os);
		}
	};

	template<typename T>
	std::ostream& operator<<(std::ostream& os, const GeneratingList<T>& rd) {
		rd.print(os);
		return os;
	}
}
#endif // !SDDS_GENERATINGLIST_H