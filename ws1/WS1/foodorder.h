#ifndef SDDS_FOODORDER_H
#define SDDS_FOODORDER_H 

extern double g_taxrate;
extern double g_dailydiscount;

namespace sdds {
	class FoodOrder {
		char m_custName[10];
		char* m_foodDesc{};
		double m_foodPrice;
		bool m_isDailySpecial;

	private:
		void set(const char* custName, const char* foodDesc, const double foodPrice, const char isDailySpecial);

		void setEmpty();

		double computeTax(double price, double tax);

		double computeDiscount(double price, double discount);

		bool isCustomerEmpty();

	public:
		FoodOrder();

		~FoodOrder();

		void read(std::istream& istr);

		void display();
	};
}

#endif