#ifndef STATE
#define STATE
#include <string>
#include <vector>
using namespace std;

struct Date
{
    int year, month, day, hour, minute;

    string get_date_str();
    static Date from_date_str(string date_str);
    void fill_current_date();
};

struct State
{
    string file_path;
    Date date;
    vector<int> indices;
    bool valid;

    State(): valid(false) {}
    void set_state(string file_path, vector<int> indices);
    void save_state();
    static State load_state(string db_path);
    static const string suffix;
    static const string delimiter;
};
#endif