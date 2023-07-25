#ifndef FILE_AND_ENCODING
#define FILE_AND_ENCODING

#include <string>
#include <vector>
using namespace std;

extern char os_path_sep;

string read_file(const string &file_path);
vector<wstring> read_file_to_lines_r(const string &file_path);
vector<wstring> read_file_to_lines(const string &file_path);
vector<string> read_file_to_lines_utf8(const string &file_path);
vector<wstring> read_file_to_lines_and_convert(const string &file_path);
wstring utf8_to_utf16(const string &utf8_str);
string utf16_to_utf8(const wstring &utf16_str);
vector<wstring> split_to_lines(const wstring &txt);
vector<wstring> filter_out_empty_lines(vector<wstring> &lines);
void trim_newline(vector<wstring> &lines);
string get_dir(string file_path);
string get_base_name(string file_path);

#endif