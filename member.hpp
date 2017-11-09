#pragma once
#include <list>
#include <string>
#include <algorithm>
//#include <functional>
//#include "comparable.hpp"

namespace crtp {
    using std::list;
    using std::string;

    //--------------------------------------------------------------------------
    template<class T>
    class member
    {
    public:
        typedef list<T>                     children_t;
        typedef typename list<T>::iterator  child_iterator;

        member(T* parent)
            : parent_(parent) {}

        T*                  parent()    { return parent_; }
        child_iterator      begin()     { return children_.begin(); }
        child_iterator      end()       { return children_.end(); }

        template<class ...Args>
        T& add_child(Args ...args) {
            children_.push_back(T(static_cast<T*>(this), args...));
            return children_.back();
        }

        T* root() {
            if (parent())
                return parent()->root();
            return this;
        }

    private:
        T*          parent_;        // ptr to derived type
        children_t  children_;      // list of derived type
    };

    //--------------------------------------------------------------------------
    class person: public member<person>
    {
    public:
        typedef member<person>   base_t;

        person(person* parent, string const& name)
            : base_t(parent), name_(name) {}

        string const&   name() const    { return name_; }

    private:
        string  name_;
    };

    //--------------------------------------------------------------------------
    bool test_member() {
        person phil(nullptr, "phil");
        phil.add_child("Ben");
        phil.add_child("Alek");

        assert(phil.begin()->name() == "Ben");
        return true;
    }
    // challenges: deleting a member: rmv from parent; in the middle of the member
}
