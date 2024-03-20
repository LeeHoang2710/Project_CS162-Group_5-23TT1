#pragma once
#include "struct_and_library.h"

Year createYear(string p_year_id);
YearNode* initYearNode(Year p_school_year);
void addNewYearNode(YearNode*& head, YearNode* new_year_node);
void removeNewYearNode(YearNode*& head, Year year);
YearNode* searchYearNode(YearNode* head, string year_id);
