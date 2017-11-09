#pragma once
#include <list>
#include <string>

namespace hier0 {
    using std::list;
    using std::string;

    class hierarchy
    {
    public:
        typedef std::list<hierarchy*>    children_t;
        typedef children_t::iterator    child_iterator;

        hierarchy(hierarchy* parent)
            : parent_(parent) {}

        hierarchy*          parent()    { return parent_; }
        child_iterator      begin()     { return children_.begin(); }
        child_iterator      end()       { return children_.end(); }

        hierarchy* root() {
            hierarchy* member = this;
            for (; member->parent() != nullptr; member = member->parent());
            return member;
        }

        template<class ...Args>
        hierarchy& add_child(Args ...args) {
            children_.push_back(new hierarchy(this, args...));
            return children_.back();
        }

    private:
        hierarchy*  parent_;
        children_t  children_;
    };

    class person : public hierarchy
    {
    public:
        person(person* parent, string const& name)
            : hierarchy(parent), name_(name)
        {}
        
    private:
        string  name_;
    };

    bool test() {
        person phil(nullptr, "Phil");
        //person ben = phil.add_child(phil, "Ben");
        return true;
    }
}
