#pragma once
#include "../struct and function/struct_and_library.h"

void inputYearId(string& year_id);
Year createYear(const string& p_year_id);
YearNode* initYearNode(const Year& p_school_year);
void appendYearNode(YearNode*& head, YearNode* new_year_node);
void updateYearId(YearNode* yearNode, const string& year_id);
bool removeYearNode(YearNode*& head, const string& year_id);
YearNode* searchYearNode(YearNode* head, const string& year_id);
void importYear(YearNode*& year_list, string filename, ifstream& fin);
void addNewYearNode(YearNode*& head, Year p_year);