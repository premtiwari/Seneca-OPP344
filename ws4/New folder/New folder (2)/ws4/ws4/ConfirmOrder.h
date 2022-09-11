#ifndef SDDS_CONFIRMORDER_H
#define SDDS_CONFIRMORDER_H
#include "Toy.h"
namespace sdds {
	class ConfirmOrder {
		const Toy** m_toy{ nullptr };
		size_t m_size{};
	public:
		ConfirmOrder();
		ConfirmOrder(const ConfirmOrder& C);
		ConfirmOrder& operator=(const ConfirmOrder& C);
		ConfirmOrder(ConfirmOrder&& C);
		ConfirmOrder& operator=(ConfirmOrder&& C);
		ConfirmOrder& operator+=(const Toy& toy);
		ConfirmOrder& operator-=(const Toy& toy);
		virtual ~ConfirmOrder();
		std::ostream& display(std::ostream& ostr = std::cout) const;
	};
	std::ostream& operator<<(std::ostream& ostr, const ConfirmOrder& C);
}
#endif // !SDDS_CONFIRMORDER_H