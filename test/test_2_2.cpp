//
// Created by rudri on 9/12/2020.
//
#include "catch.hpp"
#include "redirect_io.h"
#include "p2.h"
using namespace std;

void question_2_2_b(){
    vector<int> vec1 = {9, 10, 2, 5, 8, 4, 3, 1, 1, 10, 5, 7, 4};
    auto res = focus_values (vec1);
    copy(begin(res), end(res), ostream_iterator<int>(cout, " "));
    cout << endl;
}

TEST_CASE("Question #2_2") {
    execute_test("test_2_2.in", question_2_2_b);
}