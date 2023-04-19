#ifndef EXAMINE
#define EXAMINE
#include "materials_processing.h"
#include "state.h"
using namespace std;

vector<Unit> get_materials(string file_path);
vector<WordEntry> get_words(string file_path);
void examine_random_n_words(string file_path, int n);
void examine_random_n_units(string file_path, int n, vector<wstring> tags = {}, string mode = "any");
void examine_units_with_state(State state);
void examine_words_with_state(State state);
void examine_words_prev(string file_path);
void examine_units_prev(string file_path);
void examine_words(string file_path, string mode);
void examine_units(string file_path, string mode);
void examine(string type, string file_path, string mode);

#endif