#pragma once
#include <list>
#include <string>

namespace hier1 {
    using std::list;
    using std::string;

    template<class T>
    class tree
    {
    public:
        typedef list<T>                 children_t;
        typedef children_t::iterator    child_iterator;

        tree(T* parent) : parent_(parent) {}

        T*              parent()        { return parent_; }
        child_iterator  begin()         { return children_.begin(); }
        child_iterator  end()           { return children_.end(); }

        template<class ...Args>
        T& add_child(Args... args) {
            children_.push_back(T(this, ...args));
            return children_.back();
        }
    private:
        T*              parent_;
        children_t      children_;
    };

    class person: public tree<person>
    {
    public:
        person(person* parent, string const& name)
            : tree<person>(parent), name_(name) {}

        string const&   name() const    { return name_; }

    private:
        string  name_;
    };

    bool test() {
        return true;
    }
}
