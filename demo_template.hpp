#pragma once
#include <list>
#include <string>
#include <memory>

namespace demo {
    using std::list;
    using std::string;
    using std::unique_ptr;

    //--------------------------------------------------------------------------
    class member    // e.g. node
    {
    public:
        typedef list<member>                    children_t;
        typedef typename children_t::iterator   child_iterator;

        member(member* parent)
            : parent_(parent) {}

        member*         parent()    { return parent_; }
        child_iterator  begin()     { return children_.begin(); }
        child_iterator  end()       { return children_.end(); }

    private:
        member*         parent_;
        children_t      children_;
    };

    //--------------------------------------------------------------------------
    class person: public member
    {
    public:
        person(person* parent, string const& name)
            : member(parent), name_(name) {}

        string const& name() { return name_; }

    private:
        string  name_;
    };

    //--------------------------------------------------------------------------
    bool test_demo() {
        person phil(nullptr, "Phil");
        //person& ben = phil.add_child("Ben");
        //person& alek = phil.add_child("Alek");

        return true;
    }
}
