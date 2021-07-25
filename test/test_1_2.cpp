//
// Created by rudri on 9/12/2020.
//
#include "catch.hpp"
#include "redirect_io.h"
#include "p1.h"
using namespace std;

void question_1_2_b(){
    // contenedores
    vector <int> v1 = {3, 4};
    vector <int> v2 = {3, 4, 6, 11};
    vector <int> v3 = {2, 7, 9, 13};
    vector <int> v4 = {4, 8, 10};
    vector <int> v5 = {5};
    // buscar rango
    auto res = join_sort (vector<vector<int>>{v1, v2, v3, v4, v5});
    // muestra el resultado
    copy(begin(res), end(res), ostream_iterator<int>(cout, " "));
}

TEST_CASE("Question #1_2") {
    execute_test("test_1_2.in", question_1_2_b);
}
