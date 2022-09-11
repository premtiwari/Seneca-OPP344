#ifndef SDDS_CHILD_H
#define SDDS_CHILD_H
#include <string>
#include "Toy.h"
namespace sdds {
	class Child {
		
		std::string m_name{};
		int m_age{};
		const Toy** m_toy{ nullptr };
		size_t m_numOfToys{};
	public:
		int f{};
		int o{};
		Child();
		Child(std::string name, int age, const Toy* toys[], size_t count);
		Child( Child& C);
		Child& operator=( Child& C);
		Child(Child&& C);
		virtual ~Child();
		virtual void operator~();
		Child& operator=(Child&& C);
		size_t size() const;
		std::ostream& display(std::ostream& ostr = std::cout);
	};
	std::ostream& operator<<(std::ostream& ostr,  Child& C);
}
#endif // !SDDS_CHILD_H