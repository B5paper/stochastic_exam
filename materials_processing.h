#ifndef MATERIALS_PROCESSING
#define MATERIALS_PROCESSING
#include <string>
#include <vector>
using namespace std;

struct Unit
{
    string type;  // "uni" for unidirection, "mut" for mutual direction
    vector<wstring> tags;
    vector<wstring> content;
};

struct WordEntry
{
    wstring word;
    wstring pronunciation;
    wstring explanation;
    wstring eg;
};

Unit parse_unit(const vector<wstring> &lines, int line_start, int line_end, bool &valid_unit);
vector<Unit> parse_materials(vector<wstring> &lines);
vector<WordEntry> parse_english_words(vector<wstring> &lines);

#endif