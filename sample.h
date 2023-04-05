#ifndef SAMPLE
#define SAMPLE
#include "materials_processing.h"
using namespace std;

vector<int> random_sample(vector<int> idx, int n);
vector<int> select_random_n_units(int total_units, int n);
vector<int> select_tags(vector<Unit> &units, vector<wstring> tags, string mode = "any");

#endif