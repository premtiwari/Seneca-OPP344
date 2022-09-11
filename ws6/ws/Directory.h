#ifndef SDDS_DIRECTORY_H
#define SDDS_DIRECTORY_H
#include <vector>
#include <iostream>
#include <string>
#include "Flags.h"
#include "Resource.h"
#include "File.h"
using namespace std;

namespace sdds
{
    class Directory : public Resource {

        vector<Resource*> m_contents;

    public:


        Directory(string filename="");
                size_t size() const;

        Directory& operator+=(Resource* r);

        Resource* find(const string name, const std::vector<OpFlags>& flag= {});

        ~Directory();

      void remove(const string& S, const vector<OpFlags>& V={});

      void display(ostream& ostr, const vector<FormatFlags>& V={}) const ;
   
        
        void update_parent_path(const std::string& path);

        NodeType type() const;

        std::string path() const;

        std::string name() const;

        int count() const;


   

    };
}

#endif