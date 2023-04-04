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

Unit parse_unit(const vector<wstring> &lines, int line_start, int line_end, bool &valid_unit);
vector<Unit> parse_materials(vector<wstring> &lines);

#endif