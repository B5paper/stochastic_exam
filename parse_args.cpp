#include "parse_args.h"
#include <iostream>

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