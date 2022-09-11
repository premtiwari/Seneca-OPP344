#include <vector>
#include <iostream>
#include <string>
#include "CovidCollection.h"
using namespace std;

namespace sdds
{   

    string rtrim(const std::string &s)
    {   
        size_t end = s.find_last_not_of(" ");
        return (end == std::string::npos) ? "" : s.substr(0, end + 1);
    }



    ostream& operator<<(std::ostream& out, const Covid& theCovid)
    {   
        out<<"| ";
        out<<setw(21);
        out << left << theCovid.m_country << " | " << setw(15) << theCovid.m_city << " | " << setw(20) << theCovid.m_variant << " | ";
        out << right;
        out<<setw(6);
        if( theCovid.m_year != -1  ) out << theCovid.m_year << " | ";
        else out <<" " << " | ";
        out<<setw(4) <<theCovid.m_cases << " | " <<setw(3) << theCovid.m_deaths <<" |";

        return out;
    }


    
    CovidCollection::CovidCollection(string filename)
    {
        fstream file;
        file.open(filename);

        if (file.is_open()) {
            
            while (!file.eof()) {
        
                Covid covid;
                string str;
                int a;
                getline(file,str);
                stringstream s(str);
                char c[100];
                s.get(c,26);
               // cout<<c;
                str=c;
                if(str=="") break;
                covid.m_country = rtrim(str);
                s.get(c,26);
               // cout<<c;
                str=c;
                covid.m_city = rtrim(str); 
                s.get(c,26);
                str=c;
                covid.m_variant = rtrim(str);
                s>>a;
                covid.m_year = a > 0 ? a : -1 ;
                s>>a;
                covid.m_cases = a;
                s>>a;
                covid.m_deaths = a;
                m_covid.push_back(covid);

            }
        
        }
        else 
        {
            throw std::invalid_argument("File cannot be opened.");
        }
    
    }

    void CovidCollection::display(ostream& out) const
        {   
            int C=0, D=0;
            for_each (m_covid.begin(), m_covid.end(), [&](Covid cov)->void { 
                C+= cov.m_cases;
                D+= cov.m_deaths;
                out << cov << "\n";
            });
                out << setw(89) << setfill('-') << '\n' << setfill(' ');
                out<<"|";
                out<< setw(79) << "Total Cases Around the World: ";
                out<< setw(6) << C <<" |\n";
                out<<"|" << setw(79);
                out << "Total Deaths Around the World: " << setw(6);
                out << D <<" |\n";
            
        }

        void CovidCollection::cleanList()
        {   
            for_each (m_covid.begin(), m_covid.end(), [](Covid &cov)->void {
                if(cov.m_variant=="[None]") cov.m_variant="";
            });
        }



        list<Covid> CovidCollection::getListForCountry(string c) const
        {
            list<Covid> newdata;
            for_each (m_covid.begin(), m_covid.end(), [&](Covid cov)->void {
                if(cov.m_country==c) newdata.push_back( cov );
            });

            return newdata;        
        }


        list<Covid> CovidCollection::getListForVariant(string v) const 
        {
            list<Covid> newdata;
            for_each (m_covid.begin(), m_covid.end(), [&](Covid cov)->void {
                if(cov.m_variant==v) newdata.push_back( cov );
            });

            return newdata;   
        }

        void CovidCollection::sort(string sortt)
        {
            if(sortt=="country")
            {
                std::sort(m_covid.begin(), m_covid.end(), [](const Covid & a, const Covid & b) -> bool
                { 
                    return a.m_country < b.m_country; 
                });
            }
            else if( sortt=="variant" )
            {
                std::sort(m_covid.begin(), m_covid.end(), [](const Covid & a, const Covid & b) -> bool
                { 
                    return a.m_variant < b.m_variant; 
                });
            }
            else if( sortt=="cases" )
            {
                std::sort(m_covid.begin(), m_covid.end(), [](const Covid & a, const Covid & b) -> bool
                { 
                    return a.m_cases < b.m_cases; 
                });
            }
            else if( sortt=="deaths" )
            {
                std::sort(m_covid.begin(), m_covid.end(), [](const Covid & a, const Covid & b) -> bool
                { 
                    return a.m_deaths < b.m_deaths; 
                });
            }
        }


        bool CovidCollection::inCollection(string v) const
        {
            return  any_of(m_covid.begin(), m_covid.end(), [&](Covid cov) { return cov.m_variant==v;});
        }


}
