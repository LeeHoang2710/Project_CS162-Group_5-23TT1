#pragma once
#include "struct_and_library.h"

bool checkFailedInput();

void importSemesters(Semester* list_sem, ifstream& fin);

void createSemester(YearNode*& pHY);