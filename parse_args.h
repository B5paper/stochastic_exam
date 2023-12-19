#ifndef PARSE_ARGS_H
#define PARSE_ARGS_H
#include "examine.h"
#include <unordered_map>
#include <string>
using namespace std;

struct DomainInfo
{
    string domain_name;
    string file_path;
    string type;
};

unordered_map<string, string> parse_args(int argc, char* argv[]);
ExamInfo select_domain(vector<DomainInfo> domain_infos);
string select_mode();
ExamInfo fill_exam_info_interactively(string &exe_path);
vector<DomainInfo> parse_domain_db(string domain_db_path);
ExamInfo get_exam_info_from_args(unordered_map<string, string> &args);

#endif