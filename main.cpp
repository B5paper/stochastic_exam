#pragma execution_character_set("gbk")
#include "main.h"
#include "sample.h"
#include "file_and_encoding.h"
#include "display.h"
#include <algorithm>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <string>
#include <random>
#include <cstdlib>
#include <cstdio>
#include <cstring>
#include <iostream>
#include <codecvt>
using namespace std;

bool parse_args(int argc, char* argv[], string &file_path)
{
    if (argc != 2)
    {
        cout << "Please input a file name." << endl;
        return false;
    }
    file_path.assign(argv[1]);
    return true;
}

vector<Unit> get_materials(string file_path)
{
    vector<wstring> lines = read_file_to_lines(file_path);
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


int main(int argc, char* argv[])
{
    // parse_args(argc, argv, file_path);
    // string file_path("D:\\Documents\\Projects\\stochastic_exam\\test_data\\data_2.txt");
    // vector<Unit> units = get_materials(file_path);
    // display_unit(units[0]);
    // vector<int> indices_with_tag = select_tags(units, {L"b", L"c"}, "all");
    // auto v = move(random_sample({1, 2,3,4,5,6,7}, 4));

    // wchar environment initializaiton
    std::ios_base::sync_with_stdio(false);
    std::locale utf8( std::locale(), new std::codecvt_utf8_utf16<wchar_t> );
    std::wcout.imbue(utf8);

    // string file_path("D:\\Documents\\Projects\\stochastic_exam\\test_data\\data_1.txt");
    string file_path("D:\\Documents\\documents\\Language\\english_words.md");
    vector<WordEntry> words = get_words(file_path);
    vector<int> indices(words.size());
    for (int i = 0; i < indices.size(); ++i)
        indices[i] = i;
    vector<int> sample_indices = random_sample(indices, 5);
    for (int idx: sample_indices)
    {
        cout << "idx: " << idx << endl;
        display_word_in_qa_mode(words[idx]);
        cout << endl;
    }
    return 0;
}
