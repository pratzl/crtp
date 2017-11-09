#pragma once
#include <list>
#include <string>
#include <algorithm>
//#include <functional>
//#include "comparable.hpp"

namespace crtp2 {
    using std::list;
    using std::string;
    class people;

    //--------------------------------------------------------------------------
    template<class H, class M>
    class member
    {
    public:
        typedef list<M>                     children_t;
        typedef typename list<M>::iterator  child_iterator;

        member(H& hier, M* parent)
            : hier_(&hier), parent_(parent) {}

        H&                  hier()      { return *hier_; }
        M*                  parent()    { return parent_; }
        child_iterator      begin()     { return children_.begin(); }
        child_iterator      end()       { return children_.end(); }

        M&                  root()      { return dim().root(); }

        template<class ...Args>
        M& add_child(Args ...args) {
            children_.push_back(M(hier(), static_cast<M*>(this), args...));
            return children_.back();
        }

    private:
        H*          hier_;          // owning hierarchy
        M*          parent_;        // ptr to derived type
        children_t  children_;      // list of derived type
    };

    //--------------------------------------------------------------------------
    template<class H, class M>
    class hierarchy
    {
    public:
        template<class ...Args>
        hierarchy(Args ...args)
            : root_(static_cast<H&>(*this), nullptr, args...) {}

        M&      root()       { return root_; }

    private:
        M       root_;
    };

    //--------------------------------------------------------------------------
    class person: public member<people,person>
    {
    public:
        typedef member<people,person>   base_t;

        person(people& dim, person* parent, string const& name)
            : base_t(dim,parent), name_(name) {}

        string const&   name() const { return name_; }

    private:
        string  name_;
    };

    //--------------------------------------------------------------------------
    class people: public hierarchy<people,person>
    {
    public:
        typedef hierarchy<people, person>   base_t;

        people(string const& name)
            : base_t("root"), name_(name) {}

        string const&   name() const { return name_; }

    private:
        string  name_;
    };

    //--------------------------------------------------------------------------
    bool test_hierarchy() {
        people family("Ratzloff");
        person& phil = family.root().add_child("Phil");
        person& ben  = phil.add_child("Ben");
        person& alek = phil.add_child("Alek");
        return true;
    }

    // improvements over member-only hierarchy: root always exists; root() is O(1)
}
