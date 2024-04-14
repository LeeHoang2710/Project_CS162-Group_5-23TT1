#include "../class_helper.h"

bool importYear(YearNode*& year_list, ClassNode* allClass, string filename, ifstream& fin)
{
    fin.open(filename);
    if (!fin.is_open())
	{
		cout << "Cannot open file " << filename << endl;
		return false;
	}

    string line;
    while (getline(fin, line))
    {
        Year new_year = createYear(line, nullptr);
        getline(fin, line, '\n');
        stringstream classes(line);
        if (line == "#")
        {
            addNewYearNode(year_list, new_year);
            continue;
        }

        if (!importClassSubNode(allClass, new_year, classes))
            return false;

        for (int i = 0; i < 3; ++i)
        {
            if (fin.eof())
                break;

            getline(fin, line, '\n');
            if (line == "#")
                break;

            stringstream ss(line);
            importSemester(allClass, new_year.list_sem, ss, fin);
        }

        addNewYearNode(year_list, new_year);
    }

    fin.close();
    return true;
}

bool exportYear(YearNode*& year_list, string filename, ofstream& fout)
{
    fout.open(filename);
    if (!fout.is_open())
    {
        cout << "Cannot open file " << filename << endl;
        return false;
    }

    YearNode* currYear = year_list;
    while (currYear)
    {
        fout << currYear->school_year.year_id << endl;
        exportClassSubNode(currYear->school_year.classSublist, fout);
        exportSemesterInYear(currYear->school_year.list_sem, fout);
        currYear = currYear->next;
    }

    fout.close();
    return true;
}

ClassSubNode* createClassSubNode(ClassNode* classNode)
{
    return new ClassSubNode{classNode, nullptr};
}

void appendClassSubNode(ClassSubNode*& classSublist, ClassSubNode* classSubNode)
{
    if (!classSublist)
	{
		classSublist = classSubNode;
		return;
	}
    
    ClassSubNode* curr = classSublist;
    while (curr->next)
		curr = curr->next;
    curr->next = classSubNode;
}

ClassNode* searchClassNode(ClassNode* allClass, string class_id)
{
    ClassNode* curr = allClass;
    while (curr)
    {
        if (curr->my_class.class_id == class_id)
            return curr;
        curr = curr->next;
    }

    return nullptr;
}

bool importClassSubNode(ClassNode* allClass, Year& year, stringstream& ss)
{
    string class_id;
    while (getline(ss, class_id, ','))
    {
        ss >> class_id;
        ClassNode* classNode = searchClassNode(allClass, class_id);
        if (!classNode)
        {
            cout << "Class " << class_id << " not found" << endl;
            return false;
        }

        ClassSubNode* classSubNode = createClassSubNode(classNode);
        appendClassSubNode(year.classSublist, classSubNode);
    }

    return true;
}

void exportClassSubNode(ClassSubNode* classSublist, ofstream& fout)
{
    ClassSubNode* curr = classSublist;
	while (curr)
	{
		fout << curr->class_node->my_class.class_id << ",";
		curr = curr->next;
	}
	fout << endl;
}
