#include <iostream>
#include <string>
#include "Flags.h"
#include "File.h"
#include "Resource.h"
using namespace std;

namespace sdds
{
           std::string File::path() const{ return m_parent_path; }

        std::string File::name() const{ return m_name; }

        int File::count() const{return -1;}

        size_t File::size() const{return m_contents.length();}

        File::File(string filename,string text)
        {   
            Resource::m_name=filename;
            m_parent_path += filename;
            m_contents = text;
        }
        
        void File::update_parent_path(const std::string&path){ Resource::m_parent_path = path + m_name;}

        NodeType File::type()const{return NodeType::FILE;}

 
    
}
