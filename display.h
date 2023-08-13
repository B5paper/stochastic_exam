#ifndef DISPLAY
#define DISPLAY
#include "materials_processing.h"

void printwstr(const wchar_t *str);
void display_unit(const Unit &unit);
void display_unit_in_qa_mode(const Unit &unit, char &ctl);
void display_word(const WordEntry &word_entry);
void display_word_in_qa_mode(const WordEntry &word_entry);

#endif