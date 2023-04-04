#include "tests.h"
#include "display.h"
#include "sample.h"
#include <iostream>
#include <conio.h>
using namespace std;

void test_parse_file()
{

}

void test_parse_materials(vector<wstring> &lines)
{
    vector<Unit> units = parse_materials(lines);
    cout << "---------- test: display all units ----------" << endl;
    for (auto &unit: units)
    {
        display_unit(unit);
        cout << endl;
    }
}

void test_select_random_units(vector<Unit> &units)
{
    cout << "---------- random units ----------" << endl;
    cout << endl;
    vector<int> random_indices = move(select_random_n_units(units.size(), 3));
    for (int idx: random_indices)
    {
        cout << "idx: " << idx << endl;
        display_unit(units[idx]);
        cout << endl;
    }
}

void test_display_in_qa_mode(vector<Unit> &units, vector<int> random_indices)
{
    cout << "------ display in qa mode ------" << endl;
    for (int idx: random_indices)
    {
        cout << "(continue to next unit...)" << endl;
        getch();
        display_in_qa_mode(units[idx]);
        cout << endl;
    }
}

void test_select_tags(vector<Unit> &units, vector<wstring> &tags)
{

}