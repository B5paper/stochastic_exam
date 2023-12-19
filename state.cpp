#include "state.h"
#include "file_and_encoding.h"
#include <iostream>
#include <cstring>
#include <ctime>

// Date::Date(int year, int month, int day, int hour, int minute)
// {
//     if (year < 2023)
//     {
//         cout << "wrong param: year" << endl;
//         exit(1);
//     }
//     if (!(month >= 1 && month <= 12))
//     {
//         cout << "wrong param: month" << endl;
//         exit(1);
//     }
//     if (!(hour >= 0 && hour <= 23))
//     {
//         cout << "wrong param: hour" << endl;
//         exit(1);
//     }
//     this->year = year;
//     this->month = month;
//     this->day = day;
//     this->hour = hour;
//     this->minute = minute;
// }

string Date::get_date_str()
{
    return to_string(year) + "/" + to_string(month) + "/" + to_string(day) + " " +
    to_string(hour) + ":" + to_string(minute);
}

Date Date::from_date_str(string date_str)
{
    Date date;
    int i = 0, j = 0;
    while (j < date_str.size() && date_str[j] != '/')
        ++j;
    date.year = stoi(date_str.substr(0, j+1));
    i = j + 1;
    ++j;
    while (j < date_str.size() && date_str[j] != '/')
        ++j;
    date.month = stoi(date_str.substr(i, j - i));
    i = j + 1;
    ++j;
    while (j < date_str.size() && date_str[j] != ' ')
        ++j;
    date.day = stoi(date_str.substr(i, j - i));
    i = j + 1;
    ++j;
    while (j < date_str.size() && date_str[j] != ':')
        ++j;
    date.hour = stoi(date_str.substr(i, j - i));
    i = j + 1;
    date.minute = stoi(date_str.substr(i));
    return date;
}

void Date::fill_current_date()
{
    time_t cur_time = time(NULL);
    tm *timeinfo;
    timeinfo = localtime(&cur_time);
    this->year = 1900 + timeinfo->tm_year;
    this->month = 1 + timeinfo->tm_mon;
    this->day = timeinfo->tm_mday;
    this->hour = timeinfo->tm_hour;
    this->minute = timeinfo->tm_min;
}

const string State::suffix = "_exam_db";
const string State::delimiter = "[state]";

void State::set_state(string file_path, vector<int> indices)
{
    this->file_path = file_path;
    this->indices = indices;
    valid = true;
}

void State::save_state()
{
    if (!valid)
    {
        cout << "not a valid state, please set the state firstly." << endl;
        exit(1);
    }

    char os_path_sep = get_os_path_sep();

    string suffix = "_exam_db";
    int i = file_path.size() - 1;
    while (i >= 0 && file_path[i] != os_path_sep)
        --i;
    string dir = file_path.substr(0, i);
    int j = file_path.size() - 1;
    while (j >= 0 && file_path[j] != '.')
        --j;
    string base_name = file_path.substr(i+1, j - (i+2) + 1);
    string new_file_path = dir + os_path_sep + base_name + suffix;
    FILE *f = fopen(new_file_path.c_str(), "a");  // is "a" correct?
    if (!f)
    {
        cout << "fail to open the file: " << new_file_path << endl;
        exit(1);
    }

    fwrite(delimiter.c_str(), delimiter.length(), 1, f);
    fwrite("\n", 1, 1, f);
    fwrite(file_path.c_str(), file_path.length(), 1, f);
    fwrite("\n", 1, 1, f);
    date.fill_current_date();
    fwrite(date.get_date_str().c_str(), date.get_date_str().length(), 1, f);
    fwrite("\n", 1, 1, f);
    const char *temp_str;
    for (int i = 0; i < indices.size(); ++i)
    {
        temp_str = to_string(indices[i]).c_str();
        fwrite(temp_str, strlen(temp_str), 1, f);
        if (i != indices.size() - 1)
            fwrite(",", 1, 1, f);
    }
    fwrite("\n", 1, 1, f);
    fclose(f);
}

State State::load_state(string db_path)
{
    State state;
    vector<string> lines = read_file_to_lines_utf8(db_path);
    int n = lines.size();
    string indices_str;
    vector<int> indices;
    int p1 = 0, p2 = 0;
    int idx;
    int m;
    for (int i = n - 1; i > -1; --i)
    {
        if (lines[i] == "[state]")
        {
            state.file_path = lines[i+1];
            state.date = Date::from_date_str(lines[i+2]);
            indices_str = lines[i+3];
            m = indices_str.size();
            while (p2 < m)
            {
                while (p2 < m && indices_str[p2] != ',')
                    ++p2;
                idx = stoi(indices_str.substr(p1, p2 - p1));
                indices.push_back(idx);
                ++p2;
                p1 = p2;
            }
            break;
        }
    }
    state.indices = move(indices);
    return state;
}

string State::get_db_path_from_file_path(string file_path)
{
    string dir = get_dir(file_path);
    string base_name = get_base_name(file_path);
    char os_path_sep = get_os_path_sep();
    string db_path = dir + os_path_sep + base_name + suffix;
    return db_path;
}