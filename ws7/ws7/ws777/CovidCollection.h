#ifndef SDDS_COVIDCOLLECTION_H
#define SDDS_COVIDCOLLECTION_H
#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <iomanip>
#include <algorithm>    // std::for_each
using namespace std;

namespace sdds
{   
    string rtrim(const string &);

    struct Covid
    {
        int m_cases;
        int m_year;
        int m_deaths;
        string m_country;
        string m_city;
        string m_variant;
    };


    ostream& operator<<(ostream&, const Covid&);

    class CovidCollection  {

            vector<Covid> m_covid;  

        public:

            CovidCollection(string );
        
            void display(ostream& ) const;

            void sort(string );

            void cleanList();

            bool inCollection(string ) const;

            list<Covid> getListForCountry(string ) const;

            list<Covid> getListForVariant(string ) const;

    };

}
#endif