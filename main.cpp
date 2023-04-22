#pragma execution_character_set("gbk")
#include "main.h"
#include "examine.h"
#include "parse_args.h"
#include <unordered_map>
#include <string>
#include <iostream>
#include <codecvt>
#include <algorithm>
using namespace std;

void init_wide_char_environment()
{
    // wchar environment initializaiton
    std::ios_base::sync_with_stdio(false);
    std::locale utf8( std::locale(), new std::codecvt_utf8_utf16<wchar_t> );
    std::wcout.imbue(utf8);
}

string select_domain()
{
    unordered_map<string, string> domain_to_file_path;
    domain_to_file_path["english_words"] = "D:\\Documents\\documents\\Language\\english_words.md";
    domain_to_file_path["assembly"] = "D:\\Documents\\documents\\Programming Language\\Assembly\\asm_note_qa.md";

    cout << "Domains available:" << endl;
    for (unordered_map<string, string>::iterator iter = domain_to_file_path.begin();
        iter != domain_to_file_path.end();
        iter++)
    {
        cout << iter->first << endl;
    }
    cout << "Select one domain:" << endl;
    string domain;
    cin >> domain;
    if (domain_to_file_path.find(domain) == domain_to_file_path.end())
    {
        cout << "Not a valid domain." << endl;
        exit(1);
    }
    string file_path = domain_to_file_path[domain];
    return file_path;
}

int main(int argc, char* argv[])
{
    // string file_path = select_domain();
    unordered_map<string, string> args = parse_args(argc, argv);
    init_wide_char_environment();
    examine(args["type"], args["file"], args["mode"]);
    return 0;
}

// todo:

// 1. 增加 --domain 模式，使用 meta_db 存储所有的文件路径

// 1. 用数据库记录每次复习的 idx 列表以及这个列表对应的哈希，记录一共复习的次数，以及上次复习的时间。进入程序时，可以通过手动选择哈希值表示复习某一次的内容。可以选择删除哈希及其对应的 idx 列表。

// ./main.exe --type unit --file xxx --mode hist [--spec <hash_value>]
// 其中 hist 表示 history，spec 表示 specification
// <hash_value> 表示某个 [state] 的哈希值，类似 git log

