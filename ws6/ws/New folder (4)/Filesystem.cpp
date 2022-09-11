#include <iostream>
#include <iomanip>
#include <exception>
#include <string>
#include <type_traits>
#include <forward_list>
#include <fstream>
#include "Filesystem.h"
#include "Filesystem.h"
#include "Directory.h"
#include "Directory.h"
#include "File.h"
#include "File.h"
#include "Flags.h"
#include <sstream>  

using namespace std;
namespace sdds {

   Filesystem& Filesystem::operator+=(Resource* R) {
      if (R) {
      }
      return *this;
   }

   Directory* Filesystem::change_directory(const std::string& dir) {
      if (!dir[0]) {
         return m_root;
      } else {

         if (m_root->find(dir)) {
            m_current = dynamic_cast<sdds::Directory*>( m_root->find(dir));
            return m_current;
         } else {
            throw invalid_argument("Cannot change directory! DIR_NAME not found!");
         }
      }
      return m_current;
   }

   Directory* Filesystem::get_current_directory() const {
      return m_current;
   }


   Filesystem::Filesystem(string fileName, string rootDirectoryName) {


		ifstream file;
		file.open(fileName);

		if (file.is_open()) {
 
         m_root = new Directory(rootDirectoryName);
			m_current = m_root;


			while (!file.eof()) {

            string line;

             getline(file, line);
            
            string dir="",dir2="",file_name="",content="";

           vector<string> DIR;

            int end=0;
            for(long unsigned int i=0; i< line.length(); i++)
            {  

               m_current = m_root;

               if( line[i] =='/' )
               {
                  dir+= line[i];
                  end=i+1;

                  DIR.push_back(dir);

                  dir="";
               
               }
               else 
               {
                  dir+=line[i];
               }

            }


           
            for(long unsigned int i=end; i< line.length(); i++)
            {       
               if(line[i]=='|')
               {  bool f=false;
                  for( long unsigned int j=i+1; j< line.length() ;j++) 
                  {
                        if( line[j]!=' ' ) f=true;
                        if( f ) 
                          {   
                        
                              content += line[j];
                          }
                  }
                  f=true;
                  int spacecount=0;
                  for( long unsigned int j=line.length() -1 ; j>0 ;j--) 
                  {
                        if( line[j]!=' ' ) f=false;
                        if( f ) 
                          {   spacecount++;
                             
                          }
                  }

                  string temp="";
                  for( long unsigned int j= 0 ; j < content.length() - spacecount ;j++) 
                  {
                        temp += content[j];
                  }
                  content=temp;
                  
                  break;
               }
               else if( line[i]!=' ' )
               {
                  file_name+= line[i];
               }
            }   

            vector<string> DIR2;
            for( auto s : DIR ) 
            {
         
               std::stringstream ss;
               ss.str(s);
               ss >> dir;
               DIR2.push_back(dir);

            }

            std::stringstream ss;
            ss.str(file_name);
            ss >> file_name;

            bool isDirectory = false;
					for (auto token : DIR2) {
		
						if( token[token.length()-1] == '/' ) isDirectory = true;
                  else isDirectory = false;

   
						if (m_current->find(token) != nullptr) { 

                     
					
							if (isDirectory) {
								m_current = dynamic_cast<Directory*>(m_current->find(token));
							}
						}
						else if(isDirectory){
							
								m_current->operator+=(new Directory(token));

								m_current = dynamic_cast<Directory*>(m_current->find(token));
							
						}
					}

               if( file_name.length()!=0)
               m_current->operator+=(new File(file_name, content));

             m_current = m_root;
         
         }
			
		}
      else 
      {
         throw std::invalid_argument("File cannot be opened.");
      }

		

   }


   Filesystem::~Filesystem() {
      delete m_current;
      delete m_root;
   }


   
}