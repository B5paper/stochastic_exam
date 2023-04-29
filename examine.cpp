#include "examine.h"
#include "file_and_encoding.h"
#include "display.h"
#include "sample.h"
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
    State state;
    state.set_state(file_path, sample_indices);
    state.save_state();
}

void examine_random_n_units(string file_path, int n, vector<wstring> tags, string mode)
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
    State state;
    state.set_state(file_path, sample_indices);
    state.save_state();
}

void examine_units_with_state(State state)
{
    cout << "previous state date: " << state.date.get_date_str() << endl << endl;
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
    cout << "previous state date: " << state.date.get_date_str() << endl << endl;
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
    string db_path = State::get_db_path_from_file_path(file_path);
    State state = State::load_state(db_path);
    examine_words_with_state(state);
}

void examine_units_prev(string file_path)
{
    string db_path = State::get_db_path_from_file_path(file_path);
    State state = State::load_state(db_path);
    examine_units_with_state(state);
}

void examine_words(string file_path, string mode)
{
    if (mode == "new")
        examine_random_n_words(file_path, 7);
    else if (mode == "prev")
        examine_words_prev(file_path);
    else if (mode == "prev_rand")
        examine_words_prev_rand(file_path);
    else
    {
        cout << "unknown mode: " << mode << endl;
        exit(1);
    }
}

void examine_units(string file_path, string mode)
{
    if (mode == "new")
        examine_random_n_units(file_path, 3);
    else if (mode == "prev")
        examine_units_prev(file_path);
    else if (mode == "prev_rand")
        examine_units_prev_rand(file_path);
    else
    {
        cout << "unknown mode: " << mode << endl;
        exit(1);
    }
}

void examine(string type, string file_path, string mode)
{
    cout << "[start exam] [mode: " << mode << "]" << endl;
    if (type == "unit")
    {
        examine_units(file_path, mode);
    }
    else if (type == "word")
    {
        examine_words(file_path, mode);
    }
    else
    {
        cout << "unknown type: " << type << endl;
        exit(0);
    }
}


void examine_words_prev_rand(string file_path)
{
    string db_path = State::get_db_path_from_file_path(file_path);
    State state = State::load_state(db_path);
    shuffle(state.indices);
    examine_words_with_state(state);
}

void examine_units_prev_rand(string file_path)
{
    string db_path = State::get_db_path_from_file_path(file_path);
    State state = State::load_state(db_path);
    shuffle(state.indices);
    examine_units_with_state(state);
}

void examine(ExamInfo &exam_info)
{
    examine(exam_info.type, exam_info.file_path, exam_info.mode);
}