#ifndef SDDS_TOY_H
#define SDDS_TOY_H
#include <string>
#include <iostream>
namespace sdds {
	const double HST = 0.13;
	class Toy {
		std::string orderId{};
		std::string toyName{};
		unsigned int numOfToysToOrder{ 0 };
		double price{ 0 };
	public:
		Toy();
		virtual ~Toy();
		void update(int numItems);
		//Toy(const Toy *toy);
		std::string& ltrim(std::string& s, const char* t = " \t\n\r\f\v");
		std::string& rtrim(std::string& s, const char* t = " \t\n\r\f\v");
		std::string& trim(std::string& s, const char* t = " \t\n\r\f\v");
		void setToy(const Toy*);
		Toy(const std::string& toy);
		virtual std::ostream& display(std::ostream& ostr = std::cout)const;
	};
	std::ostream& operator<<(std::ostream& ostr, const Toy& T);
}
#endif // !SDDS_TOY_H