#ifndef SDDS_SET_H
#define SDDS_SET_H
#include <iostream>
#include <cmath>
#include "Pair.h"
#include "Collection.h"
#include <string>
namespace sdds {

    template<class T>
    class Set : public Collection<T,100>{
        
        const size_t CAPACITY = 100;

        public:

        Set(){;}
        
        bool add(const T& item) {

            for(size_t i=0;i< this->numOfElements; i++)
            {
                if( item == this->array[i] )
                {
                    return false;
                }
            }

            return Collection<T,100>::add(item);
        }

    };



    template<>
    bool Set<double>::add(const double& item){
        
        for(size_t i=0;i< this->numOfElements; i++)
        {
            if( std::fabs(item - this->array[i]) <= 0.01 )
            {
                return false;

            }
        }

        return Collection<double,100>::add(item);


    };


}
#endif // !