#ifndef TESTS
#define TESTS
#include "materials_processing.h"

void test_parse_materials(vector<wstring> &lines);
void test_select_random_units(vector<Unit> &units);
void test_display_in_qa_mode(vector<Unit> &units, vector<int> random_indices);

#endif