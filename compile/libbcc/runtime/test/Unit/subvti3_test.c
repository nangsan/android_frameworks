//===-- subvti3_test.c - Test __subvti3 -----------------------------------===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//
//
// This file tests __subvti3 for the compiler_rt library.
//
//===----------------------------------------------------------------------===//

#if __x86_64

#include "int_lib.h"
#include <stdio.h>
#include <stdlib.h>

// Returns: a - b

// Effects: aborts if a - b overflows

ti_int __subvti3(ti_int a, ti_int b);

int test__subvti3(ti_int a, ti_int b)
{
    ti_int x = __subvti3(a, b);
    ti_int expected = a - b;
    if (x != expected)
    {
        twords at;
        at.all = a;
        twords bt;
        bt.all = b;
        twords xt;
        xt.all = x;
        twords expectedt;
        expectedt.all = expected;
        printf("error in test__subvsi3(0x%.16llX%.16llX, 0x%.16llX%.16llX) = "
               "0x%.16llX%.16llX, expected 0x%.16llX%.16llX\n",
               at.s.high, at.s.low, bt.s.high, bt.s.low, xt.s.high, xt.s.low,
               expectedt.s.high, expectedt.s.low);
    }
    return x != expected;
}

#endif

int main()
{
#if __x86_64
//     test__subvti3(make_ti(0x8000000000000000LL, 0), 1);  // should abort
//     test__subvti3(0, make_ti(0x8000000000000000LL, 0));  // should abort
//     test__subvti3(1, make_ti(0x8000000000000000LL, 0));  // should abort
//     test__subvti3(make_ti(0x7FFFFFFFFFFFFFFFLL, 0xFFFFFFFFFFFFFFFFLL), -1);  // should abort
//     test__subvti3(-2, make_ti(0x7FFFFFFFFFFFFFFFLL, 0xFFFFFFFFFFFFFFFFLL));  // should abort

    if (test__subvti3(make_ti(0x8000000000000000LL, 0), -1))
        return 1;
    if (test__subvti3(make_ti(0x8000000000000000LL, 0), 0))
        return 1;
    if (test__subvti3(-1, make_ti(0x8000000000000000LL, 0)))
        return 1;
    if (test__subvti3(make_ti(0x7FFFFFFFFFFFFFFFLL, 0xFFFFFFFFFFFFFFFFLL), 1))
        return 1;
    if (test__subvti3(make_ti(0x7FFFFFFFFFFFFFFFLL, 0xFFFFFFFFFFFFFFFFLL), 0))
        return 1;
    if (test__subvti3(1, make_ti(0x7FFFFFFFFFFFFFFFLL, 0xFFFFFFFFFFFFFFFFLL)))
        return 1;
    if (test__subvti3(0, make_ti(0x7FFFFFFFFFFFFFFFLL, 0xFFFFFFFFFFFFFFFFLL)))
        return 1;
    if (test__subvti3(-1, make_ti(0x7FFFFFFFFFFFFFFFLL, 0xFFFFFFFFFFFFFFFFLL)))
        return 1;

#endif
    return 0;
}
