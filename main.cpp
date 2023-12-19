#pragma execution_character_set("gbk")
#include "file_and_encoding.h"
#include "main.h"
#include "examine.h"
#include "parse_args.h"
#include <unordered_map>
#include <string>
#include <iostream>
#include <codecvt>
#include <algorithm>
using namespace std;

int select_domain(const vector<string> &domain_names)
{
    int rtn;
    int domain_num = domain_names.size();
    cout << "input an index of the selected entity:" << endl;
    for (int i = 0; i < domain_num; ++i)
    {
        cout << i << ": " << domain_names[i] << endl;
    }
    cin >> rtn;
    if (rtn < 0 || rtn >= domain_num)
    {
        cout << "not a valid index" << endl;
        return -1;
    }
    return rtn;
}

void list_domain_qa_entities(const vector<DomainInfo> &domain_infos, const int selected_domain_idx)
{
    string domain_qa_file_path = domain_infos[selected_domain_idx].file_path;
    string domain_qa_type = domain_infos[selected_domain_idx].type;
    int entity_idx = 0;
    if (domain_qa_type == "unit")
    {
        vector<string> lines = read_file_to_lines_utf8(domain_qa_file_path);
        int start_line, end_line;
        for (int i = 0; i < lines.size(); ++i) 
        {
            string &line = lines[i];
            if (line == "[u_0]")
            {
                start_line = i + 1;
                continue;
            }
            if (line == "[u_1]")
            {
                end_line = i - 1;
                cout << entity_idx++ << ": ";
                for (int j = start_line; j <= end_line; ++j)
                {
                    cout << lines[j] << endl;
                }
                cout << endl;
            }
        }
    }
    else
    {
        cout << "type " << domain_qa_type << "not implemented" << endl;
    }
}

int main(int argc, char* argv[])
{
    init_wide_char_env();  // 这个函数可能会对 rdbuf 有影响
    // 因此在程序刚开始的时候就初始化宽字符环境
    unordered_map<string, string> args = parse_args(argc, argv);
    if (args["--mode"] == "list")
    {
        if (args.find("--meta_info_path") == args.end())
        {
            cout << "arguments not completed" << endl;
            exit(-1);
        }
        string meta_info_path = args["--meta_info_path"];
        vector<string> lines = read_file_to_lines_utf8(meta_info_path);
        if (lines.empty())
        {
            cout << "empty meta info file" << endl;
            exit(-1);
        } 
        string domain_db_path = lines[0];
        vector<DomainInfo> domain_infos = parse_domain_db(domain_db_path);
        vector<string> domain_names(domain_infos.size());
        for (int i = 0; i < domain_infos.size(); ++i)
        {
            domain_names[i] = domain_infos[i].domain_name;
        }
        int domain_idx = select_domain(domain_names);
        while (domain_idx < 0)
        {
            domain_idx = select_domain(domain_names);
        }
        cout << "Selected domain: " << domain_names[domain_idx] << endl << endl;
        list_domain_qa_entities(domain_infos, domain_idx);
        return 0;
    }

    ExamInfo exam_info = get_exam_info_from_args(args);
    examine(exam_info);
    // examine(args["type"], args["file"], args["mode"]);
    return 0;
}

// todo:

// 1. 用数据库记录每次复习的 idx 列表以及这个列表对应的哈希，记录一共复习的次数，以及上次复习的时间。进入程序时，可以通过手动选择哈希值表示复习某一次的内容。可以选择删除哈希及其对应的 idx 列表。

// ./main.exe --type unit --file xxx --mode hist [--spec <hash_value>]
// 其中 hist 表示 history，spec 表示 specification
// <hash_value> 表示某个 [state] 的哈希值，类似 git log

// 2. 数据库里必须同时指定 note 文件和对应的 log 文件存放的位置
// ./main --mode domain --meta_info_path <file_path>
// ./main --mode single_file --file_path <file_path>

