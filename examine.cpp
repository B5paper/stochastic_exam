#include "examine.h"
#include "file_and_encoding.h"
#include "display.h"
#include "sample.h"
#include "state.h"
#include <iostream>

vector<Unit> get_materials(string file_path)
{
    vector<wstring> lines = read_file_to_lines_and_convert(file_path);
    trim_newline(lines);
    vector<Unit> units = parse_materials(lines);
    return units;
}

vector<WordEntry> get_words(string file_path)
{
    vector<wstring> lines = read_file_to_lines_and_convert(file_path);
    int i;
    for (i = 0; i < lines.size(); ++i)
    {
        if (lines[i] != L"" && lines[i][0] != L'#')
        {
            break;
        }
    }
    lines.erase(lines.begin(), lines.begin() + i);
    vector<WordEntry> words = parse_english_words(lines);
    return words;
}

void examine_random_n_words(string file_path, int n)
{
    vector<WordEntry> words = get_words(file_path);
    vector<int> indices(words.size());
    for (int i = 0; i < indices.size(); ++i)
        indices[i] = i;
    vector<int> sample_indices = random_sample(indices, n);
    for (int idx: sample_indices)
    {
        cout << "idx: " << idx << endl;
        display_word_in_qa_mode(words[idx]);
        cout << endl;
    }
}

void examine_random_n_units(string file_path, int n, vector<wstring> tags = {}, string mode = "any")
{
    vector<Unit> units = get_materials(file_path);
    vector<int> indices(units.size());
    for (int i = 0; i < indices.size(); ++i)
        indices[i] = i;
    vector<int> sample_indices = random_sample(indices, n);
    // vector<int> indices_with_tag = select_tags(units, {L"b", L"c"}, "all");
    for (int idx: sample_indices) 
    {
        cout << "idx: " << idx << endl;
        display_unit_in_qa_mode(units[idx]);
        cout << endl;
    }
}

void examine_units_with_state(State state)
{
    cout << "previous state date: " << state.date.get_date_str() << endl;
    string file_path = state.file_path;
    vector<int> sample_indices = state.indices;
    vector<Unit> units = get_materials(file_path);
    for (int idx: sample_indices) 
    {
        cout << "idx: " << idx << endl;
        display_unit_in_qa_mode(units[idx]);
        cout << endl;
    }
}

void examine_words_with_state(State state)
{
    cout << "previous state date: " << state.date.get_date_str() << endl;
    string file_path = state.file_path;
    vector<int> sample_indices = state.indices;
    vector<WordEntry> words = get_words(file_path);
    for (int idx: sample_indices)
    {
        cout << "idx: " << idx << endl;
        display_word_in_qa_mode(words[idx]);
        cout << endl;
    }
}

void examine_words_prev(string file_path)
{
    string dir = get_dir(file_path);
    string base_name = get_base_name(file_path);
    string db_path = dir + '\\' + base_name + State::suffix;
    State state = State::load_state(db_path);
    examine_words_with_state(state);
}

void examine_units_prev(string file_path)
{
    string dir = get_dir(file_path);
    string base_name = get_base_name(file_path);
    string db_path = dir + '\\' + base_name + State::suffix;
    State state = State::load_state(db_path);
    examine_units_with_state(state);
}
