#pragma execution_character_set("gbk")
#include "main.h"
#include "sample.h"
#include "file_and_encoding.h"
#include "display.h"
#include "state.h"
#include "examine.h"
#include "parse_args.h"
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

void init_wide_char_environment()
{
    // wchar environment initializaiton
    std::ios_base::sync_with_stdio(false);
    std::locale utf8( std::locale(), new std::codecvt_utf8_utf16<wchar_t> );
    std::wcout.imbue(utf8);
}

int main(int argc, char* argv[])
{
    unordered_map<string, string> args = parse_args(argc, argv);
    init_wide_char_environment();
    examine(args["type"], args["file"], args["mode"]);
    return  0;
}

// todo:

// 1. 用数据库记录每次复习的 idx 列表以及这个列表对应的哈希，记录一共复习的次数，以及上次复习的时间。进入程序时，可以通过手动选择哈希值表示复习某一次的内容。可以选择删除哈希及其对应的 idx 列表。

