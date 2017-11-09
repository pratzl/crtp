#pragma once
#include "hierarchy.hpp"
#include "comparable.hpp"
#include "counter.hpp"
#include "clonable.hpp"

#include <algorithm>
#include <assert.h>

namespace crtp {
    using std::min;

    //--------------------------------------------------------------------------
    class person2 
        : public member<person2>
        , public counter<person2>
        , public relative_comparable<person2>
        , public clonable<person2>
    {
    public:
        typedef member<person2>   base_t;

        person2(person2* parent, string const& name)
            : base_t(parent), name_(name) {}

        string const&   name() const { return name_; }

    private:
        string  name_;
    };

    ptrdiff_t compare(person2 const& lhs, person2 const& rhs) {
        string const& lname = lhs.name();
        string const& rname = rhs.name();
        ptrdiff_t diff = 0;
        for (size_t i = 0; i < min(lname.size(), rname.size()); ++i) {
            diff = lname[i] - rname[i];
            if (diff)
                return diff;
        }
        return lname.size() - rname.size();
    }

    bool test_composable() {
        person2 phil(nullptr, "Phil");
        person2& ben  = phil.add_child("Ben");
        person2& alek = phil.add_child("Alek");

        assert(alek < ben);
        assert(phil > ben);
        assert(person2::objects_created == 5);      // temporaries were created
        assert(person2::objects_alive == 3);
        return true;
    }
}
