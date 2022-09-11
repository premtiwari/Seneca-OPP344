#include <vector>
#include <iostream>
#include <string>
#include "Flags.h"
#include "Resource.h"
#include "Directory.h"
#include "File.h"
using namespace std;

namespace sdds
{   


        Directory::Directory(string filename)
        {     
            if(filename[filename.length()-1] == '/') m_parent_path = filename;
            else m_parent_path += filename;
            m_name = filename;

        }

        
   
        
        void Directory::update_parent_path(const string& path)
        {

            m_parent_path = path + m_parent_path;
            for(size_t i=0; i < m_contents.size() ; i++) m_contents[i]->update_parent_path(m_parent_path);
            
        }

        NodeType Directory::type() const{  return NodeType::DIR; }

        string Directory::path() const{ return m_parent_path;}

        string Directory::name() const{ return m_name;}

        int Directory::count() const{ return m_contents.size();}

        size_t Directory::size() const
        {   
            size_t tsize=0u;

            for(size_t i=0; i <   m_contents.size() ; i++) tsize+= m_contents[i]->size();

            return tsize;
        }




        Directory& Directory::operator+=(Resource* r)
        {   
           
            for( size_t i=0; i <   m_contents.size() ; i++ ) 
                if( r->type() != NodeType::DIR && m_contents[i]->name() == r->name()) 
                    throw r;
            
            string s = m_parent_path;
            r->update_parent_path(s);
            m_contents.push_back(r);

            return *this;
        }

        Resource* Directory::find(const string name, const vector<OpFlags>& flag)
        {

            if( flag.size() > 0 )
            {   
                for(size_t i=0; i <   m_contents.size() ; i++)
                {   
                   
                    if( m_contents[i]->name() == name) return m_contents[i];
                    else if( m_contents[i]->type() == NodeType::DIR && flag[0] == OpFlags::RECURSIVE  )
                    {   
                        Directory* a = dynamic_cast<Directory*>(m_contents[i]);
                        if( a->find(name,flag) != nullptr   ) 
                            return a->find(name,flag);

                    }
                }
            }
            else
            {
                for( size_t i=0; i <   m_contents.size() ; i++ ) 
                    if( m_contents[i]->name() == name) 
                        return m_contents[i];
                
            }

            return nullptr;
        }

       



      void Directory::display(ostream& ostr, const vector<FormatFlags>& V) const {

      ostr << "Total size: " << size() << " bytes" << endl;

      for(size_t i=0; i < m_contents.size() ; i++)
      { 
         if (m_contents[i]->name().back()=='/') {
            ostr << "D" << " | ";
            ostr.setf(ios::left);
            ostr.width(15);
            ostr << m_contents[i]->name();
            ostr.unsetf(ios::left);
            ostr << " |" ;
            if (V.size()>0) {
               ostr << " " ;
               ostr.setf(ios::right);
                if(m_contents[i]->count()>=0) ostr<<" "  <<m_contents[i]->count();
                else ostr<<"  ";
               ostr<< " | ";
               ostr.width(4);
               ostr << m_contents[i]->size();
               ostr << " bytes |" ;
            }
            ostr.unsetf(ios::right);
         } else {
            ostr << "F" << " | ";
            ostr.setf(ios::left);
            ostr.width(15);
            ostr << m_contents[i]->name();
            ostr.unsetf(ios::left);
            ostr << " |";
            if (V.size()>0) {
                ostr << " " ;
               ostr.setf(ios::right);
                if(m_contents[i]->count()>=0) ostr <<" " << m_contents[i]->count();
                else ostr<<"  ";
                ostr<< " | ";
               ostr.width(4);
               ostr << m_contents[i]->size();
               ostr << " bytes |";
            }
            ostr.unsetf(ios::right);
         }
         ostr << "\n";
         
      }

    }

          void Directory::remove(const string& S, const vector<OpFlags>& V) {
         Resource* match = find(S);
         if (match) {
            if (S.back() == '/' && V.size() > 0 ) { 
                vector<Resource*>::iterator it;
                it = m_contents.begin();
                for( size_t i=0; i <   m_contents.size() ; i++ )
                {
                    if( m_contents[i]->name() == S ) { m_contents.erase(it); }
                    it++;
                }
            } else {
               throw invalid_argument(S + " is a directory. Pass the recursive flag to delete directories.");
            }
         } else {
            throw string(S + " does not exist in DIRECTORY_NAME");
         }
      }

     Directory::~Directory(){ 
         for (size_t i = 0; i < m_contents.size(); i++) 
         delete(m_contents)[i]; 
    }  
    
}

