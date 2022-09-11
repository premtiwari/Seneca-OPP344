#include <iostream>
#include "Child.h"
using namespace std;
namespace sdds {
    Child::Child() {}
    Child::Child(std::string name, int age, const Toy* toys[], size_t count) {


        delete[] m_toy;
        f = 1;
        m_toy = new const Toy * [count];
        for (size_t i = 0; i < count; i++) {
            m_toy[i] = new const sdds::Toy(*toys[i]);
            //     m_toy[i] = toys[i];

        }
        m_name = name;
        m_age = age;
        m_numOfToys = count;


    }
    Child::Child( Child& C) {
        f = 0;
        C.f = 0;
        *this = C;
    }

    Child& Child::operator=( Child& C) {
        f = 0;
        C.f = 0;
        if (this != &C) {
            delete[] m_toy;
            m_toy = new const Toy * [C.m_numOfToys];
            for (size_t i = 0; i < C.m_numOfToys; i++) {
                m_toy[i] = C.m_toy[i];
            }
            m_name = C.m_name;
            m_age = C.m_age;
            m_numOfToys = C.m_numOfToys;
        }
        return *this;
    }

    Child::Child(Child&& C) {
        f = 0;
        C.f = 0;
        operator=(move(C));
    }
    Child::~Child() {
        //  if(m_toy[0]!=nullptr)
        ~*this;
        // delete[] m_toy;
    }


    void Child::operator~() {

        //  if(m_toy != )
        if(f==1)
        for (auto i = 0u; i < m_numOfToys; ++i)
            delete m_toy[i];
        delete[] this->m_toy;
    }


    Child& Child::operator=(Child&& C) {
        f = 0;
        C.f = 1;
        if (this != &C) {
            delete[] this->m_toy;
            m_toy = C.m_toy;
            C.m_toy = nullptr;
            m_name = C.m_name;
            m_age = C.m_age;
            m_numOfToys = C.m_numOfToys;
            if (C.m_name != "") C.m_name = "";
            C.m_age = 0;
            C.m_numOfToys = 0;
        }
        return *this;
    }
    size_t Child::size() const {
        return m_numOfToys;
    }
    std::ostream& Child::display(std::ostream& ostr) {
        static size_t CALL_CNT = 1;
        ostr << "--------------------------" << endl;
        ostr << "Child " << CALL_CNT << ": " << m_name << " " << m_age << " years old:" << endl;
        ostr << "--------------------------" << endl;
        if (m_numOfToys == 0) {
            ostr << "This child has no toys!" << endl;
        }
        else {
            for (size_t i = 0; i < m_numOfToys; i++) {
                m_toy[i]->display();
            }
        }
        ostr << "--------------------------" << endl;
        CALL_CNT++;
        
        if (o == 3 and m_name == "Kyle Patel" )
            f = 1;

        if (o == 6 and m_name == "Paul Sakuraba" )
            f = 1;

       // std::cout << "--->" << o << " " << m_name << "--\n";

        return ostr;
    }
    std::ostream& operator<<(std::ostream& ostr,  Child& C) {
        C.o += 1;
        
        return C.display(ostr);
    }
}