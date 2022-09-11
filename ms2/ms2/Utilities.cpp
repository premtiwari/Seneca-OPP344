/* I have done all the coding by myself and only copied the code that my professor provided to complete my workshops and assignments.
   Name: Hayaturehman Ahmadzai
   Email: hahmadzai3@myseneca.ca
   Student ID: 122539166
   Created on 2021-07-09.*/

#include "Utilities.h"
#include <iostream>


namespace sdds {

    const std::string WHITESPACE = " \n\r\t\f\v";
 
    std::string ltrim(const std::string &s)
    {
        size_t start = s.find_first_not_of(WHITESPACE);
        return (start == std::string::npos) ? "" : s.substr(start);
    }

    char Utilities::m_delimiter{};

    void Utilities::setFieldWidth(size_t newWidth)
    {
        m_widthField = newWidth;
    }

    size_t Utilities::getFieldWidth() const
    {
        return m_widthField;
    }

    std::string Utilities::extractToken(const std::string& str, size_t& next_pos, bool& more)
    {   
        //std::cout<<"n:"<<next_pos << " get " <<getDelimiter() <<" "; 
        //std::cout<<"str:"<<str; 
        size_t idxOfDelimiter = (str.find(getDelimiter(), next_pos));
       // std::cout<<" id: "<<idxOfDelimiter;
        std::string extracted = str.substr(next_pos, idxOfDelimiter - next_pos);
       // std::cout<<" extracted:"<<extracted <<"\n"; 
        extracted=ltrim(extracted);
        if (idxOfDelimiter == next_pos)
        {
            more = false;
            throw std::string("Failed to find the delimiter");
        }

        next_pos = idxOfDelimiter + 1;

        setFieldWidth(std::max(m_widthField, extracted.size()));
        more = idxOfDelimiter != std::string::npos;

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
