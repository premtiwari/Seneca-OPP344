#ifndef SDDS_FILE_H
#define SDDS_FILE_H
#include <iostream>
#include <string>
#include "Flags.h"
#include "Resource.h"
using namespace std;

namespace sdds
{
    class File : public Resource{

        string m_contents;

    public:

        File(string filename,string text="");
        
        void update_parent_path(const std::string&path);

        NodeType type()const;

        std::string path() const;

        std::string name() const;

        int count() const;

        size_t size() const;
    };
}

#endif