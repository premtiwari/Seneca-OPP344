#ifndef SDDS_CHILD_H
#define SDDS_CHILD_H
#include <string>
#include "Toy.h"
namespace sdds {
class Child {
 std::string m_name{};
 int m_age{};
 const Toy** m_toy{nullptr};
 size_t m_numOfToys{};
public:
 Child();
 Child(std::string name, int age, const Toy* toys[], size_t count);
 Child(const Child& C);
 Child& operator=(const Child& C);
 Child(Child&& C);
 virtual ~Child();
 void operator~();
 Child& operator=(Child&& C);
 size_t size() const;
 std::ostream& display(std::ostream& ostr=std::cout) const;
};
std::ostream& operator<<(std::ostream& ostr, const Child& C);
}
#endif // !SDDS_CHILD_H