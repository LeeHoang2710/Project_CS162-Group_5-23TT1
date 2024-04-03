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
		ClassNode* currClass = searchClassNode(class_list, class_id);
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
}

void exportResults(ResultsNode* results_list, const string& filename, ofstream& fout)
{
	fout.open(filename);
	if (!fout.is_open())
	{
		cout << "Cannot open " << filename << " to export results information." << endl;
		return;
	}

	while (results_list)
	{
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

void updateCurrentSemGpa(Student& student)
{
	string currSemId = getCurrSemId(student.results_list);
	ResultsNode* currResultsNode = getCurrSemResultsNode(student.results_list, currSemId);
	float cur_gpa = 0.0f;
	unsigned short count = 0;
	while (currResultsNode)
	{
		cur_gpa += currResultsNode->results.score.overall;
		++count;
		currResultsNode = currResultsNode->next;
	}

	student.cur_gpa = cur_gpa / count;
}

void updateCurrentYearGpa(Student& student)
{
	string currYearId = getCurrYearId(student.results_list);
	ResultsNode* currResultsNode = getCurrYearResultsNode(student.results_list, currYearId);
	float total_gpa = 0.0f;
	unsigned short count = 0;

	//year gpa = average of 3 sem gpa = average of all courses in 3 sem
	while (currResultsNode)
	{
		total_gpa += currResultsNode->results.score.overall;
		++count;
		currResultsNode = currResultsNode->next;
	}

	student.total_gpa = total_gpa / count;
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

ResultsNode* appendResultsNode(ResultsNode*& results_list, ResultsNode* resultsNode)
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
	//Pass resultsNode.results.score in
	//Pass/enter -1 to skip
	if (process != -1 && process != score.process)
		score.process = process;
	if (midterm != -1 && midterm != score.midterm)
		score.midterm = midterm;
	if (final != -1 && final != score.final)
		score.final = final;
	updateCourseOverall(score);
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
