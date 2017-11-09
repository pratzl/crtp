#include "stdafx.h"

#include "basic.hpp"
#include "comparable.hpp"
#include "comparable.hpp"
#include "counter.hpp"
#include "member.hpp"
#include "hierarchy.hpp"
#include "composable.hpp"
#include "clonable.hpp"

#include "demo.hpp"

using std::cout;
using std::endl;

// sudo service ssh start
// port 2222 (avoid conflict with Windows ssh)

#define TEST_DECL           \
    int  total     = 0;     \
    int  succeeded = 0;     \
    bool result    = true;

#define TEST(X, DESC)       \
    ++total;                \
    result = ((X) != 0);    \
    succeeded += result;    \
    if(!result)             \
        std::cout << DESC << " failed"

#define TEST_SUMMARY                                                \
    std::cout << "Total tests: " << total << std::endl              \
              << "Succeded   : " << succeeded << std::endl          \
              << "Failed     : " << (total - succeeded) << endl

// https://www.youtube.com/watch?v=4AfRAVcThyA
// CRTP: 01:24:00
// Purpose: be able to "query the derived type and provide something in the base that customizes it"
//          -- Herb Sutter, CPPCon 2017

int main()
{
    TEST_DECL;
    cout << "CRTP demo" << endl;

    double ver = _MSC_VER;

    TEST(crtp::test_basic(),        "Basic");
    TEST(crtp::test_comparable(),   "Comparable");
    TEST(crtp::test_counter(),      "Counter");
    TEST(crtp::test_member(),       "Member");
    TEST(crtp2::test_hierarchy(),   "Hierarchy");
    TEST(crtp::test_clonable(),     "Clonable");

    TEST(crtp::test_composable(),   "Composable");

    TEST(demo::test_demo(),         "Demo");

    TEST_SUMMARY;
    assert(succeeded == total);
    return 0;
}
