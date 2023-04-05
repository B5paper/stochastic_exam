#include "sample.h"
#include <algorithm>
#include <random>
#include <unordered_set>
#include <iostream>
using namespace std;

vector<int> random_sample(vector<int> idx, int n)
{
    vector<int>::iterator end = sample(idx.begin(), idx.end(), idx.begin(), n, mt19937{random_device{}()});
    idx.resize(n);
    shuffle(idx.begin(), idx.end(), mt19937{random_device{}()});
    return idx;
}

vector<int> select_random_n_units(int total_units, int n)
{
    vector<int> candidates;
    for (int i = 0; i < total_units; ++i)
    {
        candidates.push_back(i);
    }
    vector<int> random_indices(n);
    sample(candidates.begin(), candidates.end(), random_indices.begin(), n,
        mt19937{random_device{}()});
    shuffle(random_indices.begin(), random_indices.end(), mt19937{random_device{}()});
    return random_indices;
}

vector<int> select_tags(vector<Unit> &units, vector<wstring> tags, string mode)
{
    // mode: "any", "all"

    vector<int> selected_indices;
    unordered_set<wstring> s;
    for (wstring &tag: tags)
    {
        s.insert(tag);
    }
    int n = units.size();
    int num_tags;
    bool valid, exist;
    if (mode == "any")
    {
        for (int i = 0; i < n; ++i)
        {
            num_tags = units[i].tags.size();
            for (int j = 0; j < num_tags; ++j)
            {
                if (s.find(units[i].tags[j]) != s.end())
                {
                    selected_indices.push_back(i);
                    break;
                }
            }
        }
    }
    else if (mode == "all")
    {
        for (int i = 0; i < n; ++i)
        {
            valid = true;
            num_tags = units[i].tags.size();
            for (int j = 0; j < tags.size(); ++j)
            {
                exist = false;
                for (int k = 0; k < num_tags; ++k)
                {
                    if (units[i].tags[k] == tags[j])
                    {
                        exist = true;
                        break;
                    }
                }
                if (!exist)
                {
                    valid = false;
                    break;
                }
            }
            if (valid)
            {
                selected_indices.push_back(i);
            }
        }
    }
    else
    {
        cout << "unrecognized mode in select_tags()" << endl;
    }
    return selected_indices;
}