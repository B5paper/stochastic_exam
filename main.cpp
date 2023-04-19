#pragma execution_character_set("gbk")
#include "main.h"
#include "sample.h"
#include "file_and_encoding.h"
#include "display.h"
#include "state.h"
#include "examine.h"
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

unordered_map<string, string> parse_args(int argc, char* argv[])
{
    /*
        --file <file_path>
        --type {word | unit}
        --mode {prev | new}
        --db <file_path>
    */
    unordered_map<string, string> args;
    for (int i = 1; i < argc; ++i)
    {
        if (argv[i] == string("--file"))
        {
            args.insert(make_pair("file", argv[i+1]));
        }
        if (argv[i] == string("--type"))
        {
            args.insert(make_pair("type", argv[i+1]));
        }
        if (argv[i] == string("--mode"))
        {
            args.insert(make_pair("mode", argv[i+1]));
        }
        if (argv[i] == string("--db"))
        {
            args.insert(make_pair("db", argv[i+1]));
        }
    }

    bool exist_db = false;
    if (args.find("mode") == args.end())
        args["mode"] = "prev";
    if (args.find("db") != args.end())
        exist_db = true;
    if (args["mode"] == "prev" && !exist_db)
    {
        cout << "please input a database file path" << endl;
        exit(1);
    }
    return args;
}

void init_wide_char_environment()
{
    // wchar environment initializaiton
    std::ios_base::sync_with_stdio(false);
    std::locale utf8( std::locale(), new std::codecvt_utf8_utf16<wchar_t> );
    std::wcout.imbue(utf8);
}

// english words: "D:\\Documents\\documents\\Language\\english_words.md"
// data_2: "D:\\Documents\\Projects\\stochastic_exam\\test_data\\data_2.txt"

int main(int argc, char* argv[])
{
    unordered_map<string, string> args = parse_args(argc, argv);
    for (auto &[key, val]: args)
    {
        cout << "key: " << key << ", val: " << val << endl;
    }
    
    init_wide_char_environment();

    string file_path = args["file"];
    if (args["type"] == "unit")
    {
        if (args["mode"] == "new")
            examine_random_n_units(file_path, 3);
        else if (args["mode"] == "prev")
            examine_units_prev(file_path);
        else
        {
            cout << "unknown mode: " << args["mode"] << endl;
            exit(1);
        }
    }
    else if (args["type"] == "word")
    {
        if (args["mode"] == "new")
            examine_random_n_words(file_path, 7);
        else if (args["mode"] == "prev")
            examine_words_prev(file_path);
        else
        {
            cout << "unknown mode: " << args["mode"] << endl;
            exit(1);
        }
    }
    else
    {
        cout << "unknown type" << endl;
        exit(0);
    }
    return  0;
}

// todo:

// 1. 进入程序时可以选择复习上次的或对新的进行采样

// 1. 用数据库记录每次复习的 idx 列表以及这个列表对应的哈希，记录一共复习的次数，以及上次复习的时间。进入程序时，可以通过手动选择哈希值表示复习某一次的内容。可以选择删除哈希及其对应的 idx 列表。

// 1. 
