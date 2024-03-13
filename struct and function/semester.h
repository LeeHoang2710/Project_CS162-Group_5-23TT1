#pragma once
#include "struct_and_library.h"

void importSemester(Semester*& list_sem, ifstream& fin);
void exportSemester(Semester* list_sem, ofstream& fout);

bool checkFailedInput();//check multiple things, maybe everything
void createSemester(YearNode*& pHY);
void deleteSemester(YearNode*& pHY);
void searchSemester(YearNode*& pHY);