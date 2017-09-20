//Programmer: Jack Wilson
//Programmer ID: 1617227

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#include <cstdlib> //for toupper()
#include <cstring>
#include "DynamicArray.h"

const string fileName = "dvc-schedule.txt";

struct Course
{
    string term, section, course, instructor, whenWhere, subjectCode;
};

struct codeSectionPair
{
    string subjectCode;
    int numSections = 0;
};

int main()
{
    //output student information
    cout << "Programmer: Jack Wilson" << endl;
    cout << "Programmer ID: 1617227" << endl;
    cout << "File: " << __FILE__ << endl;
    cout << endl;

    char* token;
    char buf[1000];
    const char* const tab = "\t";

    // open the input file
    ifstream fin;
    fin.open(fileName);
    if (!fin.good()) throw "I/O error";

    DynamicArray<Course> courses(100000);
    DynamicArray<codeSectionPair> subjectCodes(100000);
    int numSubjectCodes = 0;

    // read the input file
    int counter = 0;
    int duplicates= 0;
    while (fin.good())
    {
        // read the line
        string line;
        getline(fin, line);
        strcpy(buf, line.c_str());

        if (buf[0] == 0) continue; // skip blank lines

        //parse the line
        string term(token = strtok(buf, tab));
        string section((token = strtok(0, tab)) ? token : "");
        string course((token = strtok(0, tab)) ? token : "");
        string instructor((token = strtok(0, tab)) ? token : "");
        string whenWhere((token = strtok(0, tab)) ? token : "");
        if (course.find('-') == string::npos) continue; // invalid line: no dash in course name
        string subjectCode(course.begin(), course.begin() + course.find('-'));

        //load a course into the 'courses' array
        Course c;
        c.term = term;
        c.section = section;
        c.course = course;
        c.instructor = instructor;
        c.whenWhere = whenWhere;
        c.subjectCode = subjectCode;



        //Dedup
        bool isdup = false;
        for (int i = 0; i < counter; i++) {
            if (c.section == courses[i].section && c.term == courses[i].term) {
                isdup = true;
                break;
            }
        }
        if (isdup) {
            duplicates++;
            continue;
        }

        //count the number of unique subject codes
        int j = 0;
        for (; j < numSubjectCodes; j++) {
            if (subjectCodes[j].subjectCode == c.subjectCode) {
                break;
            }
        }
        if (j == numSubjectCodes) {
            subjectCodes[j].subjectCode = c.subjectCode;
            numSubjectCodes++;
        }
        courses[counter] = c;
        counter++;
        for (int i = 0; i < numSubjectCodes; i++) {
            if (c.subjectCode == subjectCodes[i].subjectCode) {
                subjectCodes[i].numSections++;
                break;
            }
        }

        //progress bar
        if (counter % 1000 == 0) {
            cerr << '.';
            cerr.flush( );
        }
    }
    fin.close();

    //count
    cout << endl;

    cout << "Subject codes: " << numSubjectCodes << endl;
    for (int i = 0; i < numSubjectCodes; i++) {
        cout << subjectCodes[i].subjectCode <<": " << subjectCodes[i].numSections << endl;
    }
    cout << "numClasses: " << counter << endl;
    cout <<"Duplicates: " << duplicates << endl;

    return 0;
}
