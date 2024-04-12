#include "../results.h"

void importClassResult(ClassNode* class_list, const string& filename, ifstream& fin)
{
	fin.open(filename);
	if (!fin.is_open())
	{
		cout << "Cannot open " << filename << " to import results information." << endl;
		return;
	}

	string class_id;
	while (getline(fin, class_id))
	{
		ClassNode* currClass = findClass(class_list, class_id);
		if (!currClass)
		{
			cout << "Cannot find class " << class_id << endl;
			return;
		}

		importStudentResult(currClass, fin);
	}

	fin.close();
}

void importStudentResult(ClassNode* currClass, ifstream& fin)
{
	string student;
	while (getline(fin, student) && student != "//")
	{
		istringstream iss(student);
		string student_id;
		getline(iss, student_id, ',');
		StudentNode* currStudent = searchStudentNode(currClass->my_class.student_list, student_id);
		if (!currStudent)
		{
			cout << "Cannot find student " << student_id << endl;
			return;
		}

		importCourseResult(currStudent, fin);
	}
}

void importCourseResult(StudentNode* currStudent, ifstream& fin)
{
	string result;
	while (getline(fin, result) && result != "*")
	{
		istringstream iss(result);
		string course_id, sProcess, sMidterm, sFinal;
		getline(iss, course_id, ',');
		ResultNode* currResult = searchResultNode(currStudent->student.result_list, course_id);
		if (!currResult)
		{
			cout << "Cannot find " << course_id << " ResultNode for " << currStudent->student.student_id << endl;
			return;
		}
		//skip through year_id, sem_id and go to score
		getline(iss, sProcess, ',');
		getline(iss, sProcess, ',');

		getline(iss, sProcess, ',');
		getline(iss, sMidterm, ',');
		getline(iss, sFinal, ',');

		float process = stof(sProcess),
			midterm = stof(sMidterm),
			final = stof(sFinal);
		updateScore(currResult->result.score, process, midterm, final);
	}
	updateCurrentSemGpa(currStudent);
	updateTotalGpa(currStudent);
}

void exportResult(ClassNode* class_list, const string& filename, ofstream& fout)
{
	fout.open(filename);
	if (!fout.is_open())
	{
		cout << "Cannot open " << filename << " to export results information." << endl;
		return;
	}

	while (class_list)
	{
		fout << class_list->my_class.class_id << "\n";
		StudentNode* stulist = class_list->my_class.student_list;
		while (stulist)
		{
			fout << stulist->student.student_id << ','
				<< stulist->student.first_name << "\n";
			ResultNode* result_list = stulist->student.result_list;
			while (result_list)
			{
				fout << result_list->result.course_id << ','
					<< result_list->result.year_id << ','
					<< result_list->result.sem_id << ','
					<< result_list->result.score.process << ','
					<< result_list->result.score.midterm << ','
					<< result_list->result.score.final << "\n";
				result_list = result_list->next;
			}

			stulist = stulist->next;
			fout << "*\n";
		}

		class_list = class_list->next;
		fout << "//\n";
	}

	fout.close();
}

void inputScore(float& process, float& midterm, float& final)
{
	//cout << "Enter process score: ";
	cin >> process;
	//cout << "Enter midterm score: ";
	cin >> midterm;
	//cout << "Enter final score: ";
	cin >> final;
}

void updateCourseOverall(Score& score)
{
	score.overall = score.process * 0.35 + score.midterm * 0.25 + score.final * 0.4;
}

void updateCurrentSemGpa(StudentNode* studentNode)
{
	string currSemId = getCurrSemId(studentNode->student.result_list);
	ResultNode* currResultNode = getCurrSemResultNode(studentNode->student.result_list, currSemId);
	float cur_gpa = 0.0f;
	unsigned short count = 0;
	while (currResultNode)
	{
		cur_gpa += currResultNode->result.score.overall;
		++count;
		currResultNode = currResultNode->next;
	}

	studentNode->student.cur_gpa = cur_gpa / count;
}

void updateTotalGpa(StudentNode* studentNode)
{
	ResultNode* currResultNode = studentNode->student.result_list;
	float total = 0.0f;
	unsigned short count = 0;

	while (currResultNode)
	{
		total += currResultNode->result.score.overall;
		++count;
		currResultNode = currResultNode->next;
	}

	studentNode->student.total_gpa = total / count;
}

Result createResult(const string& course_id, const string& sem_id, const string& year_id)
{
	Result newResult;
	newResult.course_id = course_id;
	newResult.sem_id = sem_id;
	newResult.year_id = year_id;
	return newResult;
}

ResultNode* createResultNode(const Result& result)
{
	return new ResultNode{ result };
}

void appendResultNode(ResultNode*& result_list, ResultNode* resultNode)
{
	if (!result_list)
		result_list = resultNode;
	else
	{
		ResultNode* curr = result_list;
		while (curr->next)
			curr = curr->next;

		curr->next = resultNode;
	}
}

void updateScore(Score& score, const float& process, const float& midterm, const float& final)
{
	//Pass ResultNode.Result.score in
	//Pass/enter -1 to skip
	if (process != -1 && process != score.process)
		score.process = process;
	if (midterm != -1 && midterm != score.midterm)
		score.midterm = midterm;
	if (final != -1 && final != score.final)
		score.final = final;
	updateCourseOverall(score);
}

string getCurrSemId(ResultNode* result_list)
{
	while (result_list->next)
		result_list = result_list->next;
	return result_list->result.sem_id;
}

string getCurrYearId(ResultNode* result_list)
{
	while (result_list->next)
		result_list = result_list->next;
	return result_list->result.year_id;
}

ResultNode* getCurrSemResultNode(ResultNode* result_list, const string& currSemId)
{
	while (result_list && result_list->result.sem_id != currSemId)
		result_list = result_list->next;
	return result_list;
}

ResultNode* getCurrYearResultNode(ResultNode* result_list, const string& currYearId)
{
	while (result_list && result_list->result.year_id != currYearId)
		result_list = result_list->next;
	return result_list;
}

ResultNode* searchResultNode(ResultNode* result_list, string courseid)
{
	while (result_list && result_list->result.course_id != courseid)
		result_list = result_list->next;

	return result_list;
}

bool removeResultNode(ResultNode*& result_list, string course_id)
{
	ResultNode* target = searchResultNode(result_list, course_id);
	if (!target)
		return false;

	ResultNode* dummy = new ResultNode;
	dummy->next = result_list;

	ResultNode* curr = dummy;
	while (curr->next != target)
		curr = curr->next;

	curr->next = target->next;
	delete target;
	result_list = dummy->next;
	delete dummy;
	return true;
}

void deleteResultList(ResultNode* result_list, string courseid)
{
	while (result_list)
	{
		ResultNode* temp = result_list;
		result_list = result_list->next;
		delete temp;
	}
}
