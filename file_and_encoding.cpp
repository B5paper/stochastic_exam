#include "file_and_encoding.h"

string read_file(const string &file_path)
{
    // read file to UTF-8

    string txt;
    FILE *f = fopen(file_path.c_str(), "r");
    const int BUFSIZE = 128;
    char buf[BUFSIZE];
    while (!feof(f))
    {
        memset(buf, 0, BUFSIZE);
        fread(buf, BUFSIZE, 1, f);
        txt.append(buf);
    }
    fclose(f);
    return txt;
}

vector<wstring> read_file_to_lines_r(const string &file_path)
{
    // read file to wchar_t, reserving the \n at the end of a line

    vector<wstring> lines;
    wstring line;
    const int BUFSIZE = 128;
    wchar_t buf[BUFSIZE];
    FILE *f = fopen(file_path.c_str(), "r");
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
    wstring_convert<codecvt_utf8_utf16<char16_t>, char16_t> convertor;
    u16string dest = convertor.from_bytes(utf8_str);
    wstring utf16_le((wchar_t*)dest.c_str());
    return utf16_le;
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


