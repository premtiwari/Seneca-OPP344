#include <iostream>
#include "Toy.h"
#include <algorithm>
using namespace std;
namespace sdds {

	// 	Toy::Toy(const Toy *toy) 
	//  {
	// 	// std::cout<<"ASdfsf";
	// 	   this->numOfToysToOrder=toy->numOfToysToOrder;
	// 	    this->orderId=toy->orderId;
	// 	   this->price=toy->price;
	// 	     this->toyName=toy->toyName;

	//   }
	Toy::~Toy() {};
	Toy::Toy() {}
	void Toy::update(int numItems) {
		numOfToysToOrder = numItems;
	}
	string& Toy::ltrim(string& s, const char* t) {
		s.erase(0, s.find_first_not_of(t));
		return s;
	}
	string& Toy::rtrim(string& s, const char* t) {
		s.erase(s.find_last_not_of(t) + 1);
		return s;
	}
	string& Toy::trim(string& s, const char* t) {
		return ltrim(rtrim(s, t), t);
	}
	Toy::Toy(const string& toy) {
		string delimiter = ":";
		size_t start = 0;

		size_t end = toy.find(delimiter);
		orderId = toy.substr(start, end - start);
		orderId = trim(orderId);

		start = end + delimiter.size();
		end = toy.find(delimiter, start);
		toyName = toy.substr(start, end - start);
		toyName = trim(toyName);

		start = end + delimiter.size();
		end = toy.find(delimiter, start);
		string temp = toy.substr(start, end - start);
		numOfToysToOrder = stoi(trim(temp));

		start = end + delimiter.size();
		end = toy.find(delimiter, start);
		temp = toy.substr(start, end - start);
		price = stod(trim(temp));
	}
	ostream& Toy::display(ostream& ostr) const {
		ostr << "Toy ";
		ostr.width(8);
		ostr << orderId << ":";
		ostr.width(18);
		ostr.setf(ios::right);
		ostr << toyName;
		ostr.width(3);
		ostr << numOfToysToOrder << " items";
		ostr.width(8);
		ostr << price << "/item subtotal:";
		ostr.width(7);
		ostr.setf(ios::fixed);
		ostr.precision(2);
		ostr << numOfToysToOrder * price << " tax:";
		ostr.width(6);
		ostr << numOfToysToOrder * price * HST << " total:";
		ostr.width(7);
		ostr << (numOfToysToOrder * price) * (1 + HST) << endl;
		return ostr;
	}
	ostream& operator<<(ostream& ostr, const Toy& T) {
		return T.display(ostr);
	}
}