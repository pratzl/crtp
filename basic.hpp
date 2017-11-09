#pragma once

namespace crtp {
    // From Wikipedia article on CRTP
    // https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern
    
    //--------------------------------------------------------------------------
    template<class T>
    struct Base
    {
        int answer() const  { return 42; }
    };

    //--------------------------------------------------------------------------
    class Derived : public Base<Derived>
    {
    };


    //--------------------------------------------------------------------------
    bool test_basic() {
        Derived derived;
        int result = derived.answer();
        return true;
    }

} // namespace crtp
