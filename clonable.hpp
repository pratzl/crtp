#pragma once

namespace crtp {
    //--------------------------------------------------------------------------
    struct Shape
    {
        virtual Shape*  clone() const =0;
        virtual ~Shape() {}
    };

    //--------------------------------------------------------------------------
    template<class T>
    struct clonable
    {
        /*virtual?*/ T* clone()
        { return new T(static_cast<T&>(*this)); }
    };

    //--------------------------------------------------------------------------
    class myobj2: public clonable<myobj2>
    {
        int answer() { return 42; }
    };

    //--------------------------------------------------------------------------
    bool test_clonable() {
        myobj2 obj1;
        myobj2* obj2 = obj1.clone();
        delete obj2;

        return true;
    }
}
