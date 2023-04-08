#include "materials_processing.h"
#include <iostream>


Unit parse_unit(const vector<wstring> &lines, int line_start, int line_end, bool &valid_unit)
{
    Unit unit;
    int i = line_start;
    int start, end, j;  // 必须要写到外面，lldb 调试时才能显示出来，不清楚为什么
    wstring line;
    while (i <= line_end)
    {
        if (lines[i].substr(0, 3) == L"[m_")
        {
            unit.type = "mut";
            unit.content.push_back(lines[i+1]);
            i += 2;
        }
        else if (lines[i].substr(0, 3) == L"[u_")
        {
            // TODO: process multiple lines
            unit.type = "uni";
            unit.content.push_back(wstring());
            ++i;
            while (i <= line_end)
            {
                if (lines[i].substr(0, 3) == L"[u_" ||
                    lines[i].substr(0, 6) == L"[unit]" ||
                    lines[i].substr(0, 5) == L"[tag]")
                    break;
                unit.content.back().append(lines[i]);
                unit.content.back().push_back(L'\n');
                ++i;
            }
        }
        else if (lines[i].substr(0, 6) == L"[unit]")
        {
            ++i;
        }
        else if (lines[i].substr(0, 5) == L"[tag]")
        {
            line = lines[i+1];
            start = 0;
            end = (int) line.size() - 1;
            j = 0;
            while (j <= end)
            {
                while (j <= end && (line[j] != L',' && line[j] != L' '))
                    ++j;
                unit.tags.push_back(line.substr(start, j - 1 - start + 1));
                while (j <= end && (line[j] == L',' || line[j] == L' '))
                    ++j;
                start = j;
            }
            i += 2;
        }
        else
        {
            wcout << L"unrecognized label: " << lines[i] << endl;
            valid_unit = false;
            return unit;
        }
    }
    valid_unit = true;
    return unit;
}

vector<Unit> parse_materials(vector<wstring> &lines)
{
    // lines should be clear material units without any extra titles or headlines

    vector<Unit> units;
    int line_idx = 0;
    int line_num = lines.size();
    int line_start, line_end;
    bool valid_unit = false;
    while (line_idx < line_num)
    {
        if (lines[line_idx] == L"[unit]")
        {
            line_start = line_idx;
            while (line_idx < line_num - 1 && lines[line_idx+1] != L"[unit]")
                ++line_idx;
            while (lines[line_idx] == L"")
                --line_idx;
            line_end = line_idx;
            Unit unit = parse_unit(lines, line_start, line_end, valid_unit);
            if (valid_unit)
            {
                units.emplace_back(move(unit));
            }
            else
            {
                wcout << L"error when parsing materials" << endl;
            }
            ++line_idx;
        }
        else if (lines[line_idx] == L"")
        {
            ++line_idx;
        }
    }
    return units;
}


vector<wstring> part_of_speeches{L"adj.", L"n.", L"v.", L"vi.", L"vt.", L"verb.", 
    L"count-n.", L"uncount-n.", L"phrase."};

vector<WordEntry> parse_english_words(vector<wstring> &lines)
{
    vector<WordEntry> words;
    WordEntry word_entry;
    int n = lines.size();
    int idx_pron, idx_exp, idx_eg;  // pronunciation, explanation, e.g. 
    wstring exp;
    for (int i = 0; i < n; ++i)
    {
        if (lines[i] == L"")
            continue;
        idx_pron = lines[i].find(L" pron. ");
        idx_pron = idx_pron == string::npos ? -1 : idx_pron + 7;
        int j = 0;
        while (j < part_of_speeches.size())
        {
            idx_exp = lines[i].find(L" " + part_of_speeches[j] + L" ");
            if (idx_exp != string::npos)
                break;
            ++j;
        }
        if (idx_exp == string::npos)
        {
            cout << "fail to parse english word" << endl;
            wcout << lines[i] << endl;
            return words;
        }
        idx_exp = idx_exp + 1;
        idx_eg = lines[i].find(L" eg. ");
        idx_eg = idx_eg == string::npos ? -1 : idx_eg + 5;

        word_entry.word = lines[i].substr(0, idx_exp - 2 - 0 + 1);

        if (idx_pron != -1)
        {
            word_entry.pronunciation = lines[i].substr(idx_pron, idx_exp - 2 - idx_pron + 1);
        }
        else
        {
            word_entry.pronunciation = L"";
        }

        if (idx_eg != -1)
        {
            word_entry.explanation = lines[i].substr(idx_exp, idx_eg - 6 - idx_exp + 1);
        }
        else
        {
            word_entry.explanation = lines[i].substr(idx_exp);   
        }

        if (idx_eg != -1)
        {
            word_entry.eg = lines[i].substr(idx_eg);
        }
        else
        {
            word_entry.eg = L"";
        }
       
        words.push_back(word_entry);
    }
    return words;
}