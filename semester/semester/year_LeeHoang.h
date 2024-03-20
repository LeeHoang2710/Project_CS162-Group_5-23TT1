#pragma once
#include "struct_and_library.h"

Year createYear(string p_year_id);
YearNode* initYearNode(Year school_year);
void addNewYearNode(YearNode*& head, Year year);
void removeNewYearNode(YearNode*& head, Year year);
YearNode* searchYearNode(YearNode* head, Year year);