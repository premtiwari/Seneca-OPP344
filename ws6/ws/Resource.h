// Workshop 6 - STL Containers
// 2021/12/05 - Gideon

#ifndef SDDS_EVENT_H
#define SDDS_EVENT_H


#include <iostream>
#include <string>
#include "Flags.h"

namespace sdds {
    class Resource {
    protected:
        std::string m_name{};
        std::string m_parent_path = "/";

    public:
        virtual void update_parent_path(const std::string&) = 0;
        virtual std::string name() const = 0;
        virtual int count() const = 0;
        virtual std::string path() const = 0;
        virtual size_t size() const = 0;
        virtual NodeType type() const = 0;
        virtual ~Resource() {}
    };
}  

#endif