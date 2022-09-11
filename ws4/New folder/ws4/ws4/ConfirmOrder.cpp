#include "ConfirmOrder.h"
using namespace std;
namespace sdds {
	ConfirmOrder::ConfirmOrder() {}
	ConfirmOrder::ConfirmOrder(const ConfirmOrder& C) {
		operator=(C);
	}
	ConfirmOrder& ConfirmOrder::operator=(const ConfirmOrder& C) {
		if (this != &C) {
			delete[] m_toy;
			m_toy = new const Toy * [C.m_size];
			for (size_t i = 0; i < C.m_size; i++) {
				m_toy[i] = C.m_toy[i];
			}
			m_size = C.m_size;
		}
		return *this;
	}
	ConfirmOrder::ConfirmOrder(ConfirmOrder&& C) {
		operator=(move(C));
	}
	ConfirmOrder& ConfirmOrder::operator=(ConfirmOrder&& C) {
		if (this != &C) {
			delete[] m_toy;
			m_toy = C.m_toy;
			//m_toy = move(C.m_toy);
			C.m_toy = nullptr;
			m_size = C.m_size;
			C.m_size = 0;
		}
		return *this;
	}
	ConfirmOrder& ConfirmOrder::operator+=(const Toy& toy) {
		bool found = false;
		for (size_t i = 0; i < m_size; i++) {
			if (&toy == m_toy[i]) {
				found = true;
			}
		}
		if (!found) {
			const Toy** temps = new const Toy * [m_size + 1];
			for (size_t i = 0; i < m_size; i++) {
				temps[i] = m_toy[i];
			}
			delete[] m_toy;
			m_toy = temps;
			temps[m_size] = &toy;
			m_size++;
			//m_toy = move(temps);
		}
		return *this;
	}
	ConfirmOrder& ConfirmOrder::operator-=(const Toy& toy) {
		for (size_t i = 0; i < 5; i++) {
			if (&toy == m_toy[i]) {
				m_toy[i] = nullptr;
				m_size--;
			}
		}
		return *this;
	}
	ConfirmOrder::~ConfirmOrder() {
		delete[] m_toy;
	}
	ostream& ConfirmOrder::display(ostream& ostr) const {
		ostr << "--------------------------" << endl;
		ostr << "Confirmations to Send" << endl;
		ostr << "--------------------------" << endl;
		if (m_size == 0) {
			ostr << "There are no confirmations to send!" << endl;
		}
		else {
			for (size_t i = 0; i < m_size; i++) {
				m_toy[i]->display();
			}
		}
		ostr << "--------------------------" << endl;
		return ostr;
	}
	ostream& operator<<(ostream& ostr, const ConfirmOrder& C) {
		return C.display(ostr);
	}
}