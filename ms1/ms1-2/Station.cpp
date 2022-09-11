/* I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
   Name: Hayaturehman Ahmadzai
   Email: hahmadzai3@myseneca.ca
   Student ID: 122539166
   Created on 2021-07-09.*/

#include <iostream>
#include <iomanip>
#include "Utilities.h"
#include "Station.h"

using namespace std;

namespace sdds {
    
    size_t Station::id_generator = 1;

    size_t Station::m_widthField = 0;
    

    Station::Station(const string& record)
    {
        m_id = id_generator++;

        size_t npos = 0;
        
        bool more;

        Utilities utils;

        try {

            m_name = utils.extractToken(record, npos, more);

            m_nextSerial = stoi(utils.extractToken(record, npos, more));

            m_stockQty = stoi(utils.extractToken(record, npos, more));

            m_widthField = max(utils.getFieldWidth(), m_widthField);

            m_desc = utils.extractToken(record, npos, more);

        } catch (string& err) {

            cout << err;

        }
    }

    const string& Station::getItemName() const
    {
        return m_name;
    }

    size_t Station::getNextSerialNumber()
    {
        return m_nextSerial++;
    }

    size_t Station::getQuantity() const
    {
        return m_stockQty;
    }

    void Station::updateQuantity()
    {
        if (0 > --m_stockQty) m_stockQty = 0;
    }

    void Station::display(ostream& os, bool full) const
    {
        os << setfill('0') << setw(3) << right << m_id;
        
        os << " | " << setw(m_widthField) << setfill(' ') << left << m_name;

        os << " | " << setfill('0') << setw(6) << right << m_nextSerial << " | " ;

        if (full) {

            os << right << setw(4) << setfill(' ') << m_stockQty << " | ";

            os << left <<  m_desc << endl;

        }
        
        else os << endl;
    }
}
