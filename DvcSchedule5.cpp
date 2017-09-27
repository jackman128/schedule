//Programmer: Jack Wilson
//Programmer ID: 1617227

#include <iostream>
#include <string>
#include <fstream>
#include <functional>

using namespace std;

#include <cstring>
#include "DynamicArray.h"

const string fileName = "half.txt";

struct Course
{
  string term, course, instructor, whenWhere, subjectCode;
  short section;
};

struct CodeSectionPair
{
  string subjectCode;
  int numSections = 0;
};

struct SectionsForTerm
{
  int sectionsSeen = 0;
  DynamicArray<short> seenSectionNumber;
};

unsigned termToIndex(const string &str);

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

  //open the input file
  ifstream fin;
  fin.open(fileName);
  if (!fin.good()) throw "I/O error";

  //'courses' will hold all of the courses that have been processed so far
  DynamicArray<Course> courses(100000);
  //subjectCodes will hold the subject codes seen so far
  //and the number of courses for each subject.
  DynamicArray<CodeSectionPair> subjectCodes(200);

  DynamicArray<SectionsForTerm> alreadySeen(200);

  int numSubjectCodes = 0;
  int numCourses = 0;
  int duplicates= 0;
  while (fin.good()) {
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

    //'c' is the current course we are looking at
    Course c;
    c.term = term;
    c.section = static_cast<short>(atoi(section.c_str()));
    c.course = course;
    c.instructor = instructor;
    c.whenWhere = whenWhere;
    c.subjectCode = subjectCode;

    //Dedup
    bool isDup = false;
    unsigned hash = termToIndex(term + section);
    for (int i = 0; i < alreadySeen[hash].sectionsSeen; i++) {
      if (alreadySeen[hash].seenSectionNumber[i] == c.section) {
        isDup = true;
        break;
      }
    }
    if (isDup) {
      duplicates++;
      continue;
    }
    int ind = alreadySeen[hash].sectionsSeen++;
    alreadySeen[hash].seenSectionNumber[ind] = c.section;

    //count
    //If a new subject code is found, add it to subjectCodes
    //and increment numSubjectCodes
    int j = 0;
    for (; j < numSubjectCodes; j++) {
      if (subjectCodes[j].subjectCode == c.subjectCode) {
        //subject code for this course matches an existing subject code
        subjectCodes[j].numSections++;
        break;
      }
    }
    //if the end of the previous loop was reached, then this is a new subject code.
    if (j == numSubjectCodes) {
      subjectCodes[j].subjectCode = c.subjectCode;
      subjectCodes[j].numSections++;
      numSubjectCodes++;
    }
    //add this course to the courses array and increment the number of courses.
    courses[numCourses] = c;
    numCourses++;

    //progress bar
    if (numCourses % 1000 == 0) {
      cerr << '.';
      cerr.flush( );
    }
  }
  fin.close();

  //insertion sort subjectCodes by subjectCode in alphabetical order
  int i = 1;
  while (i < numSubjectCodes) {
    CodeSectionPair t = subjectCodes[i];
    int j = i - 1;
    while (j >= 0 && subjectCodes[j].subjectCode > t.subjectCode) {
      subjectCodes[j + 1] = subjectCodes[j];
      j--;
    }
    subjectCodes[j + 1] = t;
    i++;
  }

  //Now print out the number of subject codes, the array of subject codes
  //along with the number of sections
  cout << endl << endl;
  cout << "Subject codes: " << numSubjectCodes << endl;
  for (int i = 0; i < numSubjectCodes; i++) {
    cout << subjectCodes[i].subjectCode <<": " << subjectCodes[i].numSections << endl;
  }
  cout << endl;
  cout << "Duplicates: " << duplicates << endl;

  return 0;
}

unsigned termToIndex(const string &str)
{
  static hash<string> hasher;
  return hasher(str) % 512;
  /*
  string seasonStr = str.substr(0, str.find(" "));
  string yearStr = str.substr(str.find(" "));

  int seasonNum;
  if (seasonStr == "Fall")
    seasonNum = 0;
  else if (seasonStr == "Spring")
    seasonNum = 1;
  else
    seasonNum = 2;

  return stoi(yearStr) * 3 - 6003 + seasonNum;
  */
}
