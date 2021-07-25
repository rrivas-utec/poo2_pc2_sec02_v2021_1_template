//
// Created by rudri on 9/12/2020.
//
#include "catch.hpp"
#include "redirect_io.h"
#include "p1.h"
using namespace std;

void question_1_1_b(){
    // contenedores
    vector <int> v1 = {2, 3, 4};
    vector <int> v2 = {3, 4, 6, 11};
    vector <int> v3 = {6, 7, 9, 13};
    vector <int> v4 = {5, 8, 10};
    vector <int> v5 = {1, 3, 5};
    vector <vector <int>> vj = {v1, v2, v3, v4, v5};
    // sorted number
    auto res = join_sort (vj);
    // muestra el resultado
    copy(begin(res), end(res), ostream_iterator<int>(cout, " "));
}
TEST_CASE("Question #1_1") {
    execute_test("test_1_1.in", question_1_1_b);
}