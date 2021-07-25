//
// Created by rudri on 9/12/2020.
//
#include "catch.hpp"
#include "redirect_io.h"
#include "binary_tree.h"
using namespace std;

void question_3_2_b(){
    binary_tree<int> bt2(0);
    // Izquierda
    auto n1 = bt2.add_left(bt2.get_root(), 1);
    auto n11 = bt2.add_left(n1, 11);
    auto n12 = bt2.add_right(n1, 12);
    auto n121 = bt2.add_left(n12, 121);
    auto n122 = bt2.add_right(n12, 122);
    // Derecha
    auto n2 = bt2.add_right(bt2.get_root(), 2);
    auto n21 = bt2.add_left(n2, 21);
    auto n22 = bt2.add_right(n2, 22);
    auto n211 = bt2.add_left(n21, 211);
    auto n212 = bt2.add_right(n21, 212);

    // Calcula distancia
    cout << bt2.calculate_distance (n11, n122) << endl; // 2
    cout << bt2.calculate_distance (n121, bt2.get_root()) << endl; // 2
    cout << bt2.calculate_distance (n121, n212) << endl; // 2
}

TEST_CASE("Question #3_2") {
    execute_test("test_3_2.in", question_3_2_b);
}