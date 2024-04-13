#include "../results.h"

void importClassResults(ClassNode* class_list, const string& filename, ifstream& fin)
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

		importStudentResults(currClass, fin);
	}

	fin.close();
}

void importStudentResults(ClassNode* currClass, ifstream& fin)
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

		importCourseResults(currStudent, fin);
	}
}

void importCourseResults(StudentNode* currStudent, ifstream& fin)
{
	string results;
	while (getline(fin, results) && results != "*")
	{
		istringstream iss(results);
		string course_id, sProcess, sMidterm, sFinal;
		getline(iss, course_id, ',');
		ResultsNode* currResults = searchResultsNode(currStudent->student.results_list, course_id);
		if (!currResults)
		{
			cout << "Cannot find " << course_id << " ResultsNode for " << currStudent->student.student_id << endl;
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
		updateScore(currResults->results.score, process, midterm, final);
	}
	updateCurrentSemGpa(currStudent);
	updateTotalGpa(currStudent);
}

void exportResults(ClassNode* class_list, const string& filename, ofstream& fout)
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
			ResultsNode* results_list = stulist->student.results_list;
			while (results_list)
			{
				fout << results_list->results.course_id << ','
					<< results_list->results.year_id << ','
					<< results_list->results.sem_id << ','
					<< results_list->results.score.process << ','
					<< results_list->results.score.midterm << ','
					<< results_list->results.score.final << "\n";
				results_list = results_list->next;
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
	string currSemId = getCurrSemId(studentNode->student.results_list);
	ResultsNode* currResultsNode = getCurrSemResultsNode(studentNode->student.results_list, currSemId);
	float cur_gpa = 0.0f;
	unsigned short count = 0;
	while (currResultsNode)
	{
		cur_gpa += currResultsNode->results.score.overall;
		++count;
		currResultsNode = currResultsNode->next;
	}

	studentNode->student.cur_gpa = cur_gpa / count;
}

void updateTotalGpa(StudentNode* studentNode)
{
	ResultsNode* currResultsNode = studentNode->student.results_list;
	float total = 0.0f;
	unsigned short count = 0;

	while (currResultsNode)
	{
		total += currResultsNode->results.score.overall;
		++count;
		currResultsNode = currResultsNode->next;
	}

	studentNode->student.total_gpa = total / count;
}

Results createResults(const string& course_id, const string& sem_id, const string& year_id)
{
	Results newResults;
	newResults.course_id = course_id;
	newResults.sem_id = sem_id;
	newResults.year_id = year_id;
	return newResults;
}

ResultsNode* createResultsNode(const Results& results)
{
	return new ResultsNode{ results };
}

void appendResultsNode(ResultsNode*& results_list, ResultsNode* resultsNode)
{
	if (!results_list)
		results_list = resultsNode;
	else
	{
		ResultsNode* curr = results_list;
		while (curr->next)
			curr = curr->next;

		curr->next = resultsNode;
	}
}

void updateScore(Score& score, const float& process, const float& midterm, const float& final)
{
	//Pass ResultsNode.Results.score in
	//Pass/enter -1 to skip
	if (process != -1 && process != score.process)
		score.process = process;
	if (midterm != -1 && midterm != score.midterm)
		score.midterm = midterm;
	if (final != -1 && final != score.final)
		score.final = final;
	updateCourseOverall(score);
}

void addResultsNodeToClass(ClassNode* classNode, const string& year_id, const string& sem_id, const string& course_id)
{
	StudentNode* currStudent = classNode->my_class.student_list;
	while (currStudent)
	{
		Results newResults = createResults(course_id, sem_id, year_id);
		ResultsNode* newResultsNode = createResultsNode(newResults);
		appendResultsNode(currStudent->student.results_list, newResultsNode);
		currStudent = currStudent->next;
	}
}

string getCurrSemId(ResultsNode* results_list)
{
	while (results_list->next)
		results_list = results_list->next;
	return results_list->results.sem_id;
}

string getCurrYearId(ResultsNode* results_list)
{
	while (results_list->next)
		results_list = results_list->next;
	return results_list->results.year_id;
}

ResultsNode* getCurrSemResultsNode(ResultsNode* results_list, const string& currSemId)
{
	while (results_list && results_list->results.sem_id != currSemId)
		results_list = results_list->next;
	return results_list;
}

ResultsNode* getCurrYearResultsNode(ResultsNode* results_list, const string& currYearId)
{
	while (results_list && results_list->results.year_id != currYearId)
		results_list = results_list->next;
	return results_list;
}

ResultsNode* searchResultsNode(ResultsNode* results_list, string courseid)
{
	while (results_list && results_list->results.course_id != courseid)
		results_list = results_list->next;

	return results_list;
}

bool removeResultsNode(ResultsNode*& results_list, string course_id)
{
	ResultsNode* target = searchResultsNode(results_list, course_id);
	if (!target)
		return false;

	ResultsNode* dummy = new ResultsNode;
	dummy->next = results_list;

	ResultsNode* curr = dummy;
	while (curr->next != target)
		curr = curr->next;

	curr->next = target->next;
	delete target;
	results_list = dummy->next;
	delete dummy;
	return true;
}

void deleteResultsList(ResultsNode* results_list, string courseid)
{
	while (results_list)
	{
		ResultsNode* temp = results_list;
		results_list = results_list->next;
		delete temp;
	}
}
