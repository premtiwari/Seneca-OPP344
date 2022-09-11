#include <iostream>
#include "Child.h"
using namespace std;
namespace sdds {
Child::Child(){}
Child::Child(std::string name, int age, const Toy* toys[], size_t count) {
 m_toy = new const Toy*[count];
 for (size_t i = 0; i < count; i++) {
     m_toy[i] = new const Toy(toys[i]);
   // m_toy[i] = toys[i];
 }
 m_name = name;
 m_age = age;
 m_numOfToys = count;
}
Child::Child(const Child& C) {
 operator=(C);
}
Child& Child::operator=(const Child& C) {
    
   // if (this == &C)     ~*this;


    if (this != &C) {

        for (size_t i = 0; i < m_numOfToys; i++) {
            delete m_toy[i];
        }
        delete[] m_toy;

        m_toy = new const Toy * [C.m_numOfToys];
        for (size_t i = 0; i < C.m_numOfToys; i++) {
      
            //if (this == &C) delete C.m_toy[i];
            m_toy[i] = new const Toy(C.m_toy[i]);
        }
       

        m_name = C.m_name;
        m_age = C.m_age;
        m_numOfToys = C.m_numOfToys;

    }
    
    

 return *this;
}

Child::Child(Child&& C) {
 operator=(move(C));
}
Child::~Child() {

~*this;


}
void Child::operator~()
{
   // cout << "+++++++++++++++++++++++++++";
    for (size_t i = 0; i < m_numOfToys; i++) {
        delete m_toy[i];
    }

 delete[] m_toy;
}


Child& Child::operator=(Child&& C) {
 if (this != &C) {

  delete[] m_toy;
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
std::ostream& Child::display(std::ostream& ostr) const {
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
 return ostr;
}
std::ostream& operator<<(std::ostream& ostr, const Child& C) {
 return C.display(ostr);
}
}