#pragma execution_character_set("gbk")
#include <iostream>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <string>
#include <random>
#include <cstdlib>
#include <cstdio>
using namespace std;
#include <cstring>
#include <locale>
#include <codecvt>
#include <iostream>
#include <conio.h>
#include "file_and_encoding.cpp"

void printwstr(const wchar_t *str)
{
    wcout << str << endl;
}

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

struct Unit
{
    string type;  // "uni" for unidirection, "mut" for mutual direction
    vector<wstring> tags;
    vector<wstring> content;
};

Unit parse_unit(const vector<wstring> &lines, int line_start, int line_end, bool &valid_unit)
{
    Unit unit;
    int i = line_start;
    while (i <= line_end)
    {
        if (lines[i].substr(0, 3) == L"[m_")
        {
            unit.type = "mut";
            unit.content.push_back(lines[i+1]);
            i += 2;
        }
        else if (lines[i].substr(0, 3) == L"[u_")
        {
            unit.type = "uni";
            unit.content.push_back(lines[i+1]);
            i += 2;
        }
        else if (lines[i].substr(0, 6) == L"[unit]")
        {
            ++i;
        }
        else if (lines[i].substr(0, 5) == L"[tag]")
        {
            unit.tags.push_back(lines[i+1]);
            i += 2;
        }
        else
        {
            wcout << L"unrecognized label: " << lines[i] << endl;
            valid_unit = false;
            return unit;
        }
    }
    valid_unit = true;
    return unit;
}

vector<Unit> parse_materials(vector<wstring> &lines)
{
    // lines should be clear material units without any extra titles or headlines

    vector<Unit> units;
    int line_idx = 0;
    int line_num = lines.size();
    int line_start, line_end;
    bool valid_unit = false;
    while (line_idx < line_num)
    {
        if (lines[line_idx] == L"[unit]")
        {
            line_start = line_idx;
            while (line_idx < line_num - 1 && lines[line_idx+1] != L"[unit]")
                ++line_idx;
            line_end = line_idx;
            Unit unit = parse_unit(lines, line_start, line_end, valid_unit);
            if (valid_unit)
            {
                units.emplace_back(move(unit));
            }
            else
            {
                wcout << L"error when parsing materials" << endl;
            }
            ++line_idx;
        }
    }
    return units;
}

void display_unit(const Unit &unit)
{
    if (unit.type == "uni")
    {
        cout << "Type: uni" << endl;
        for (int i = 0; i < unit.content.size(); ++i)
        {
            cout << "Node " << i << ": " << endl;
            wcout << unit.content[i] << endl;
        }
    }
    else if (unit.type == "mut")
    {
        cout << "Type: mut" << endl;
        for (int i = 0; i < unit.content.size(); ++i)
        {
            cout << "Node " << i << ": " << endl;
            wcout << unit.content[i] << endl;
        }
    }
    else
    {
        cout << "unrecognized unit type in display_unit function." << endl;
    }
}

vector<int> select_random_n_units(int total_units, int n)
{
    vector<int> candidates;
    for (int i = 0; i < total_units; ++i)
    {
        candidates.push_back(i);
    }
    vector<int> random_indices(n);
    sample(candidates.begin(), candidates.end(), random_indices.begin(), n,
        mt19937{random_device{}()});
    shuffle(random_indices.begin(), random_indices.end(), mt19937{random_device{}()});
    return random_indices;
}

void display_in_qa_mode(const Unit &unit)
{
    // display unit in questioin and answer mode
    if (unit.type == "uni")
    {
        cout << "Type: uni" << endl;
        cout << "Node 0:" << endl;
        wcout << unit.content[0] << endl;
        for (int i = 1; i < unit.content.size(); ++i)
        {
            getch();
            cout << "Node " << i << ":" << endl;
            wcout << unit.content[i] << endl;
        }
    }
    else if (unit.type == "mut")
    {
        cout << "Type: mut (type any key to continue...)" << endl;
        vector<int> shuffled_indices(unit.content.size());
        for (int i = 0; i < unit.content.size(); ++i)
            shuffled_indices[i] = i;
        shuffle(shuffled_indices.begin(), shuffled_indices.end(),
            mt19937{random_device{}()});
        for (int i: shuffled_indices)
        {
            getch();
            cout << "Node " << i << ": " << endl;
            wcout << unit.content[i] << endl;
        }
    }
    else
    {
        cout << "unrecognized unit type in display_unit function." << endl;
    }
}

int main(int argc, char* argv[])
{
    string file_path;
    parse_args(argc, argv, file_path);
    // file_path.assign("D:/Documents/documents/Language/english_words.md");
    file_path.assign("D:\\Documents\\Projects\\stochastic_exam\\aaa.txt");
    vector<wstring> lines = read_file_to_lines(file_path);
    lines = filter_out_empty_lines(lines);
    trim_newline(lines);
    
    vector<Unit> units = parse_materials(lines);
    cout << endl;
    for (auto &unit: units)
    {
        display_unit(unit);
        cout << endl;
    }

    cout << "---------- random units ----------" << endl;
    cout << endl;
    vector<int> random_indices = move(select_random_n_units(units.size(), 3));
    for (int idx: random_indices)
    {
        cout << "idx: " << idx << endl;
        display_unit(units[idx]);
        cout << endl;
    }

    cout << "------ display in qa mode ------" << endl;
    for (int idx: random_indices)
    {
        cout << "(continue to next unit...)" << endl;
        getch();
        display_in_qa_mode(units[idx]);
        cout << endl;
    }
    int a = 2;
    return 0;
}