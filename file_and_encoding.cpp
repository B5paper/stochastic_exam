#include "file_and_encoding.h"
#include <locale>
#include <codecvt>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>

string read_file(const string &file_path)
{
    // read file to UTF-8

    string txt;
    FILE *f = fopen(file_path.c_str(), "r");
    const int BUFSIZE = 128;
    char buf[BUFSIZE];
    buf[BUFSIZE - 1] = '\0';  // fread() 不会把 buf 当作一个字符串，所以需要自己手动设置
    while (!feof(f))
    {
        memset(buf, 0, BUFSIZE);
        fread(buf, BUFSIZE - 1, 1, f);
        txt.append(buf);
    }
    fclose(f);
    return txt;
}

vector<string> read_file_to_lines_utf8(const string &file_path)
{
    vector<string> lines;
    string line;
    const int BUFSIZE = 128;
    char buf[BUFSIZE];
    FILE *f = fopen(file_path.c_str(), "r");
    if (!f)
    {
        cout << "fail to open the file: " << file_path << endl;
        exit(1);
        return lines;
    }
    while (!feof(f))
    {
        line.clear();
        do
        {
            buf[BUFSIZE - 2] = '\0';
            fgets(buf, BUFSIZE, f);
            line.append(buf);
        } while (buf[BUFSIZE - 2] != '\0' && buf[BUFSIZE - 2] != '\n');
        if (line.back() == '\n')  // 文件的最后一行可能没有`\n`
            line.erase(line.size() - 1);
        // 这里有 bug，有时间研究一下
        // 如果一个文件只有一行，并且没有 \n，那么 fgets() 会触发 eof
        // 紧接着 !feof() 为 false，从而跳过 if 语句，什么都读不到
        if (!feof(f))  // 如果最后一行是正常读取，那么不会触发 eof。只有再次读取后，才会触发 eof
            lines.push_back(line);
    }
    fclose(f);
    return lines;
}

vector<wstring> read_file_to_lines_and_convert(const string &file_path)
{
    vector<wstring> lines;
    string line;
    wstring wline;
    const int BUFSIZE = 128;
    char buf[BUFSIZE];
    FILE *f = fopen(file_path.c_str(), "r");
    if (!f)
    {
        cout << "fail to open the file: " << file_path << endl;
        return lines;
    }
    int i = 0;
    while (!feof(f))
    {
        ++i;
        line.clear();
        do
        {
            buf[BUFSIZE - 2] = '\0';
            fgets(buf, BUFSIZE, f);
            line.append(buf);
        } while (buf[BUFSIZE - 2] != '\0' && buf[BUFSIZE - 2] != '\n' && !feof(f));
        if (line.back() == '\n')  // 文件的最后一行可能没有`\n`
            line.erase(line.size() - 1);
        if (!feof(f))  // 如果最后一行是正常读取，那么不会触发 eof。只有再次读取后，才会触发 eof
        {
            wline = utf8_to_utf16(line);
            lines.push_back(wline);
        }
    }
    fclose(f);
    return lines;
}

vector<wstring> read_file_to_lines_r(const string &file_path)
{
    // read file to wchar_t, reserving the \n at the end of a line

    vector<wstring> lines;
    wstring line;
    const int BUFSIZE = 128;
    wchar_t buf[BUFSIZE];
    FILE *f = fopen(file_path.c_str(), "r");
    if (!f)
    {
        cout << "fail to open the file: " << file_path << endl;
        return lines;
    }
    while (!feof(f))
    {
        line.clear();
        do
        {
            buf[BUFSIZE - 2] = L'\0';
            fgetws(buf, BUFSIZE, f);
            line.append(buf);
        } while (buf[BUFSIZE - 2] != L'\0' && buf[BUFSIZE - 2] != L'\n');
        lines.push_back(line);
    }
    fclose(f);
    return lines;
}

vector<wstring> read_file_to_lines(const string &file_path)
{
    vector<wstring> lines;
    lines = move(read_file_to_lines_r(file_path));
    for (wstring &line: lines)
        line.erase(line.size() - 1);
    return lines;
}

wstring utf8_to_utf16(const string &utf8_str)
{
    wstring_convert<codecvt_utf8_utf16<wchar_t>, wchar_t> convertor;
    wstring utf16_le = convertor.from_bytes(utf8_str);
    // wstring utf16_le((wchar_t*)dest.c_str());
    if (convertor.state() == codecvt_base::result::noconv)
    {
        cout << "source encoding and destination encoding are the same." << endl;
    }
    else if (convertor.state() == codecvt_base::result::error)
    {
        cout << "fail to convert utf8 string to utf16 string" << endl;
    } 
    else if (convertor.state() == codecvt_base::result::partial)
    {
        cout << "partially convert some characters" << endl;
    }
    return utf16_le;
}

string utf16_to_utf8(const wstring &utf16_str)
{
    wstring_convert<codecvt_utf8_utf16<wchar_t>, wchar_t> convertor;
    string utf8_str = convertor.to_bytes(utf16_str);
    return utf8_str;
}

vector<wstring> split_to_lines(const wstring &txt)
{
    vector<wstring> lines;
    return lines;
}

vector<wstring> filter_out_empty_lines(vector<wstring> &lines)
{
    auto end = remove_copy_if(lines.begin(), lines.end(),
        lines.begin(), [](wstring &s) {
            return s == L"\n" || s == L"";
        });
    return vector<wstring>(lines.begin(), end);
}

void trim_newline(vector<wstring> &lines)
{
    for (int i = 0; i < lines.size(); ++i)
    {
        if (lines[i].back() == L'\n')
            lines[i].erase(lines[i].length() - 1);
    }
}

string get_dir(string file_path)
{
    int n = file_path.size();
    int i = n - 1;
    while (i > -1 && file_path[i] != '\\')
        --i;
    return file_path.substr(0, i);
}

string get_base_name(string file_path)
{
    int n = file_path.size();
    int i = n - 1;
    while (i > -1 && file_path[i] != '\\')
        --i;
    int j = n - 1;
    while (j > -1 && file_path[j] != '.')
        --j;
    return file_path.substr(i+1, j-(i+1));
}


