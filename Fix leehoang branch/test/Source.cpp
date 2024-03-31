#include <iostream>
#include "../struct_and_function/function.h"

int main() {
	YearNode* yearlist = nullptr;
	ifstream fin;
	ofstream fout;
	string filename = "../database/course.csv";
	fout.close();
	importYear(yearlist, filename, fin);
	exportYear(yearlist, "../test/test.csv", fout);
}