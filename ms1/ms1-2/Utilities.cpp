
#include "Utilities.h"
#include <iostream>

using namespace std;

namespace sdds {



    char Utilities::m_delimiter{};

    void Utilities::setFieldWidth(size_t newWidth)
    {
        m_widthField = newWidth;
    }

    size_t Utilities::getFieldWidth() const
    {
        return m_widthField;
    }

    const string WHITESPACE = " \n\r\t\f\v";
 
    string ltrim(const string &s)
    {
        size_t start = s.find_first_not_of(WHITESPACE);
        
        return (start == string::npos) ? "" : s.substr(start);
    }

    string Utilities::extractToken(const string& str, size_t& next_pos, bool& more)
    {   

        size_t idxOfDelimiter = (str.find(getDelimiter(), next_pos));
      
        string extracted = str.substr(next_pos, idxOfDelimiter - next_pos);
    
        extracted=ltrim(extracted);

        if (idxOfDelimiter == next_pos)
        {
            more = false;
            throw string("Failed to find the delimiter");
        }

        next_pos = idxOfDelimiter + 1;

        setFieldWidth(max(m_widthField, extracted.size()));

        more = idxOfDelimiter != string::npos;

        return extracted;
    }

    void Utilities::setDelimiter(char newDelimiter)
    {
        m_delimiter = newDelimiter;
    }

    char Utilities::getDelimiter()
    {
        return m_delimiter;
    }
}
