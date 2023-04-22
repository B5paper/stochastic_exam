#include "parse_args.h"
#include <iostream>

unordered_map<string, string> parse_args(int argc, char* argv[])
{
    /*
        --domain -> 列出可用 domain，要求选择一项 (自动补全 --type) -> 选择 mode (默认为 prev)
        --file <file_path>
        --type {word | unit}
        --mode {prev | new | prev_rand}
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