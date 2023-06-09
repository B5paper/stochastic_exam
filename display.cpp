#include "display.h"
#include "materials_processing.h"
#include <iostream>
#include <conio.h>
#include <algorithm>
#include <random>

void printwstr(const wchar_t *str)
{
    wcout << str << endl;
}

void display_unit(const Unit &unit)
{
    cout << "---------- unit start ----------" << endl;
    if (unit.type == "uni")
    {
        cout << "Type: uni" << endl;
        for (int i = 0; i < unit.content.size(); ++i)
        {
            cout << "Node " << i << ": " << endl;
            wcout << unit.content[i] << endl;
        }
    }
    else if (unit.type == "mut")
    {
        cout << "Type: mut" << endl;
        for (int i = 0; i < unit.content.size(); ++i)
        {
            cout << "Node " << i << ": " << endl;
            wcout << unit.content[i] << endl;
        }
    }
    else
    {
        cout << "unrecognized unit type in display_unit function." << endl;
    }
    cout << "---------- unit end ----------" << endl;
    cout << endl;
}


void display_unit_in_qa_mode(const Unit &unit)
{
    // display unit in questioin and answer mode
    if (unit.type == "uni")
    {
        cout << "Type: uni" << endl;
        cout << "Node 0:" << endl;
        wcout << unit.content[0] << endl;
        for (int i = 1; i < unit.content.size(); ++i)
        {
            getch();
            cout << "Node " << i << ":" << endl;
            wcout << unit.content[i] << endl;
        }
    }
    else if (unit.type == "mut")
    {
        cout << "Type: mut (type any key to continue...)" << endl;
        vector<int> shuffled_indices(unit.content.size());
        for (int i = 0; i < unit.content.size(); ++i)
            shuffled_indices[i] = i;
        shuffle(shuffled_indices.begin(), shuffled_indices.end(),
            mt19937{random_device{}()});
        for (int i: shuffled_indices)
        {
            getch();
            cout << "Node " << i << ": " << endl;
            wcout << unit.content[i] << endl;
        }
    }
    else
    {
        cout << "unrecognized unit type in display_unit function." << endl;
    }
    getch();
}


void display_word(const WordEntry &word_entry)
{
    wcout << word_entry.word << endl;
    if (word_entry.pronunciation != L"")
    {
        wcout << word_entry.pronunciation << endl;
    }
    wcout << word_entry.explanation << endl;
    if (word_entry.eg != L"")
    {
        wcout << L"eg. " << word_entry.eg << endl;
    }
}


void display_word_in_qa_mode(const WordEntry &word_entry)
{
    wcout << word_entry.word << endl;
    getch();
    if (word_entry.pronunciation != L"")
    {
        wcout << L"prn. " << word_entry.pronunciation << endl;
    }
    wcout << word_entry.explanation << endl;
    if (word_entry.eg != L"")
    {
        wcout << L"eg. " << word_entry.eg << endl;
    }
    getch();
}
