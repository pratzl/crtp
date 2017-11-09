#pragma once

namespace crtp {
    // from Wikipedia article on CRTP
    // https://en.wikipedia.org/wiki/Curiously_recurring_template_pattern

    //--------------------------------------------------------------------------
    template<class T>
    struct counter
    {
        static int objects_created;
        static int objects_alive;

        counter() {
            ++objects_created;
            ++objects_alive;
        }
        counter(counter const&) {
            ++objects_created;
            ++objects_alive;
        }

    protected:
        ~counter() // objects should never be removed through pointers of this type
            { --objects_alive; }
    };
    template <typename T> int counter<T>::objects_created(0);
    template <typename T> int counter<T>::objects_alive(0);

    //--------------------------------------------------------------------------
    struct myobj: public counter<myobj>
    {
        int answer() const   { return 42; }
    };

    //--------------------------------------------------------------------------
    bool test_counter() {
        for (int k = 0; k < 5; ++k) {
            myobj mo;
            assert(myobj::objects_alive == 1);
            assert(myobj::objects_created == k + 1);
        }

        assert(myobj::objects_alive == 0);
        assert(myobj::objects_created == 5);
        return true;
    }

} // namespace crtp
