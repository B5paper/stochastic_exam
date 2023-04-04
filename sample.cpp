#include "sample.h"
#include <algorithm>
#include <random>
#include <unordered_set>

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

vector<int> select_tags(vector<Unit> &units, vector<wstring> tags)
{
    vector<int> selected_indices;
    unordered_set<wstring> s;
    for (wstring &tag: tags)
    {
        s.insert(tag);
    }
    int n = units.size();
    int num_tags;
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
    return selected_indices;
}