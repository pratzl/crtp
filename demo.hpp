#pragma once
#include <list>
#include <string>
#include <memory>

namespace demo {
    using std::list;
    using std::string;
    using std::unique_ptr;

    //--------------------------------------------------------------------------
	template<class M>
    class member    // e.g. node
    {
    public:
        typedef list<M>							children_t;
        typedef typename children_t::iterator   child_iterator;

        member(M* parent)
            : parent_(parent) {}

        M*				parent()    { return parent_; }
        child_iterator  begin()     { return children_.begin(); }
        child_iterator  end()       { return children_.end(); }
		template<class ...Args>
		M& add_child(Args ...args) {
			children_.push_back(M(static_cast<M*>(this),args...));
			return children_.back();
		}
    private:
        M*				parent_;
        children_t      children_;
    };

    //--------------------------------------------------------------------------
    class person: public member<person>
    {
    public:
        person(person* parent, string const& name)
            : member<person>(parent), name_(name) {}

        string const& name() { return name_; }

    private:
        string  name_;
    };

    //--------------------------------------------------------------------------
    bool test_demo() {
        person phil(nullptr, "Phil");
        person& ben = phil.add_child("Ben");
        //person& alek = phil.add_child("Alek");

        return true;
    }
}
