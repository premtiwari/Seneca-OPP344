/* I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
   Name: Hayaturehman Ahmadzai
   Email: hahmadzai3@myseneca.ca
   Student ID: 122539166
   Created on 2021-07-09.*/

#ifndef SDDS_STATION_H
#define SDDS_STATION_H

#include <string>

using namespace std;

namespace sdds {
    class Station {

        int m_id;

        string m_name;

        string m_desc;

        int m_stockQty;

        static size_t m_widthField;
        
        static size_t id_generator;

        int m_nextSerial;


    public:

        size_t getQuantity() const;

        void updateQuantity();

        void display(ostream& os, bool full) const;

        Station(const string& record);

        const string& getItemName() const;

        size_t getNextSerialNumber();

    };
}


#endif //SDDS_STATION_H
