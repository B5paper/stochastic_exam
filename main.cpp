#pragma execution_character_set("gbk")
#include "main.h"
#include "sample.h"
#include "file_and_encoding.h"
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


using namespace std;

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


int main(int argc, char* argv[])
{
    string file_path;
    parse_args(argc, argv, file_path);
    // file_path.assign("D:/Documents/documents/Language/english_words.md");
    file_path.assign("D:\\Documents\\Projects\\stochastic_exam\\aaa.txt");
    vector<wstring> lines = read_file_to_lines(file_path);
    lines = filter_out_empty_lines(lines);
    trim_newline(lines);
    cout << endl;

    vector<Unit> units = parse_materials(lines);
    vector<int> indices_with_tag = select_tags(units, {L"b"});
    
    int a = 2;
    return 0;
}