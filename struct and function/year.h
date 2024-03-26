#pragma once
#include "struct_and_library.h"

Year createYear(const string& p_year_id);
YearNode* initYearNode(const Year& p_school_year);
void appendYearNode(YearNode*& head, YearNode* new_year_node);
bool removeYearNode(YearNode*& head, const string& year_id);
YearNode* searchYearNode(YearNode* head, const string& year_id);
