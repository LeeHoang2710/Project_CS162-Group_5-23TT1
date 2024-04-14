#pragma once
#include "struct_and_library.h"

void inputYearId(string& year_id);

Year createYear(string p_year_id, ClassNode* allclass);
YearNode* initYearNode(Year p_school_year);
void addNewYearNode(YearNode*& head, Year p_year);

void updateYearId(YearNode* yearNode, const string& year_id);

void removeNewYearNode(YearNode*& head, Year year);

YearNode* searchYearNode(YearNode* head, string year);
