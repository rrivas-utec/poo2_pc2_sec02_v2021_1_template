//
// Created by rudri on 9/12/2020.
//
#include "catch.hpp"
#include "redirect_io.h"
#include "global.h"
#include "p2.h"
using namespace std;

void question_2_1_b(){
    vector<int> vec1 = {11, 12, 3, 4, 15, 8, 11, 4, 3, 3, 12, 8, 9};
    auto res = focus_values (vec1);
    copy(begin(res), end(res), ostream_iterator<int>(cout, " "));
    cout << endl;
}


TEST_CASE("Question #2_1") {
    execute_test("test_2_1.in", question_2_1_b);
}