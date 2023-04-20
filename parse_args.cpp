#include "parse_args.h"
#include <iostream>

unordered_map<string, string> parse_args(int argc, char* argv[])
{
    /*
        --file <file_path>
        --type {word | unit}
        --mode {prev | new}
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
    }

    if (args.find("mode") == args.end())
        args["mode"] = "prev";
    return args;
}