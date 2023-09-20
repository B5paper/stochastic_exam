#include "parse_args.h"
#include "file_and_encoding.h"
#include <iostream>
#include "system_info.h"

extern char os_path_sep;

void args_to_pairs(unordered_map<string, string> &args, int argc, char **argv)
{

}


unordered_map<string, string> parse_args(int argc, char* argv[])
{
    /*
        --domain -> 列出可用 domain，要求选择一项 (自动补全 --type) -> 选择 mode (默认为 prev)
        --file <file_path>
        --type {word | unit}
        --mode {prev | new | prev_rand | seq}
    */
    unordered_map<string, string> args;

    // args to pairs
    args["exe_path"] = argv[0];
    for (int i = 1; i < argc - 1; i += 2)
    {
        args[argv[i]] = argv[i+1];
    }
    return args;

    for (int i = 1; i < argc; ++i)
    {
        if (argv[i] == string("--file"))
        {
            args.insert(make_pair("file", argv[i+1]));
        }
        else if (argv[i] == string("--type"))
        {
            args.insert(make_pair("type", argv[i+1]));
        }
        else if (argv[i] == string("--mode"))
        {
            args.insert(make_pair("mode", argv[i+1]));
        }
        else if (argv[i] == string("--domain"))
        {
            args.emplace("mode", argv[i+1]);
        }
        else if (argv[i] == "file_path")
        {
            args.emplace("file_path", argv[i+1]);
        }
        else if (argv[i] == "meta_info_path")
        {
            args.emplace("meta_info_path", argv[i+1]);
        }
        else
        {
            // cout << "unknown argument: " << argv[i] << endl;
            // exit(1);
        }
    }
    return args;
}

vector<DomainInfo> parse_domain_db(string domain_db_path)
{
    vector<string> lines = read_file_to_lines_utf8(domain_db_path);
    string dir_path = get_dir(domain_db_path);
    string file_path;
    vector<DomainInfo> domain_infos;
    for (int i = 0; i < lines.size(); ++i)
    {
        if (lines[i] == "" || lines[i] == "\n")
            continue;
        const string &line = lines[i];
        DomainInfo domain_info;
        int j = 0;
        int start = 0;
        while (j < line.size() && line[j] != ',') ++j;
        domain_info.domain_name = line.substr(0, j);
        ++j;
        start = j;
        while (j < line.size() && line[j] != ',') ++j;
        file_path = line.substr(start, (j-1) - start + 1);
        domain_info.file_path = dir_path + os_path_sep + file_path;
        domain_info.type = line.substr(j+1);
        domain_infos.push_back(domain_info);
    }
    return domain_infos;
}

ExamInfo select_domain(vector<DomainInfo> domain_infos)
{
    cout << "Available domains:" << endl;
    int i = 0;
    for (const DomainInfo &domain_info: domain_infos)
    {
        cout << i << ": " << domain_info.domain_name << endl;
        ++i;
    }
    cout << endl;
    cout << "Select one domain:" << endl;
    int domain_idx;
    cin >> domain_idx;
    if (domain_idx >= domain_infos.size())
    {
        cout << "Not a valid domain." << endl;
        exit(1);
    }
    ExamInfo exam_info;
    exam_info.file_path = domain_infos[domain_idx].file_path;
    exam_info.type = domain_infos[domain_idx].type;
    cout << endl;
    return exam_info;
}

ExamInfo fill_exam_info_interactively(string &domain_db_path)
{
    vector<DomainInfo> domain_qa_infos = parse_domain_db(domain_db_path);
    ExamInfo exam_info;
    exam_info = select_domain(domain_qa_infos);
    exam_info.mode = select_mode();
    return exam_info;
}

string select_mode()
{
    string mode;
    vector<string> mode_candidates{"new", "prev", "prev_rand", "seq"};
    cout << "Select a mode: (input the mode name) [default: seq]" << endl;
    for (int i = 0; i < mode_candidates.size(); ++i)
    {
        cout << i << ": " << mode_candidates[i] << endl;
    }
    cin >> mode;
    if (mode.empty())
        mode = "seq";
    return mode;
}

ExamInfo get_exam_info_from_args(unordered_map<string, string> &args)
{
    cout << endl;
    ExamInfo exam_info;
    if (args.find("--mode") == args.end())
    {
        cout << "unsupported arguments" << endl;
        exit(-1);
    }
    if (args["--mode"] != "domain")
    {
        cout << "unsupported mode" << endl;
        exit(-1);
    }
    if (args.find("--meta_info_path") == args.end())
    {
        cout << "domain mode must come with --meta_info_path arg" << endl;
        exit(-1);
    }

    // --mode domain
    string meta_info_path = args["--meta_info_path"];
    vector<string> lines = read_file_to_lines_utf8(meta_info_path);
    if (lines.empty())
    {
        cout << "the meta info path is empty" << endl;
    }
    string domain_db_path = lines[0];
    exam_info = fill_exam_info_interactively(domain_db_path);
    cout << endl;
    return exam_info;
    
    if (args.find("mode") == args.end())
    {
        exam_info.mode = "prev";
    }
    return exam_info;
}