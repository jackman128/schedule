//Programmer: Jack Wilson
//Programmer ID: 1617227

#include <iostream>
#include <string>
#include <fstream>
#include <functional>

using namespace std;

#include <cstring>
#include "DynamicArray.h"

const string fileName = "dvc-schedule.txt";

struct Course
{
  short term, section;
};

struct CodeSectionPair
{
  string subjectCode;
  int numSections = 0;
};

struct SectionsForTerm
{
  int sectionsSeen = 0;
  DynamicArray<Course> seenSectionNumber = DynamicArray<Course>(8);
};

short termToShort(char *str);

const int NUM_BUCKETS = 256;

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
  //subjectCodes will hold the subject codes seen so far
  //and the number of courses for each subject.
  //CodeSectionPair subjectCodes[200];

  SectionsForTerm seen[NUM_BUCKETS];

  hash<int> hasher;

  int numSubjectCodes = 0;
  int numCourses = 0;
  int duplicates= 0;
  string line;
  getline(fin, line);
  while (fin.good()) {
    Course c;
    // read the line
    getline(fin, line);
    strcpy(buf, line.c_str());

    if (buf[0] == 0) continue; // skip blank lines

    //parse the line
    c.term = termToShort(token = strtok(buf, tab));
    c.section = atoi((token = strtok(0, tab)) ? token : "");
    //string course((token = strtok(0, tab)) ? token : "");
    //string instructor((token = strtok(0, tab)) ? token : "");
    //string whenWhere((token = strtok(0, tab)) ? token : "");
    //if (course.find('-') == string::npos) continue; // invalid line: no dash in course name
    //string subjectCode(course.begin(), course.begin() + course.find('-'));

    //Dedup
    bool isDup = false;
    unsigned hash = hasher(c.section + c.term) % NUM_BUCKETS;
    for (int i = 0; i < seen[hash].sectionsSeen; i++) {
      if (c.term == seen[hash].seenSectionNumber[i].term && c.section == seen[hash].seenSectionNumber[i].section) {
        isDup = true;
        duplicates++;
        break;
      }
    }
    if (!isDup) {
      seen[hash].seenSectionNumber[seen[hash].sectionsSeen++] = c;
    }
    /*
    //count
    //If a new subject code is found, add it to subjectCodes
    //and increment numSubjectCodes
    int j = 0;
    for (; j < numSubjectCodes; j++) {
      if (subjectCodes[j].subjectCode == subjectCode) {
        //subject code for this course matches an existing subject code
        subjectCodes[j].numSections++;
        break;
      }
    }
    //if the end of the previous loop was reached, then this is a new subject code.
    if (j == numSubjectCodes) {
      subjectCodes[j].subjectCode = subjectCode;
      subjectCodes[j].numSections++;
      numSubjectCodes++;
    }
    //add this course to the courses array and increment the number of courses.
    numCourses++;
    */
  }
  fin.close();

  //insertion sort subjectCodes by subjectCode in alphabetical order
  /*
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
  cout << endl;
  cout << "Subject codes: " << numSubjectCodes << endl;
  for (int i = 0; i < numSubjectCodes; i++) {
    cout << subjectCodes[i].subjectCode <<": " << subjectCodes[i].numSections << endl;
  }
  cout << endl;
  */
  cout << "Duplicates: " << duplicates << endl;

  return 0;
}

short termToShort(char *str)
{
  /*
  const char* const space = " ";
  char  *tok;
  char *seasonStr = (tok = strtok(str, space));
  int year = atoi(tok);

  int seasonNum;
  if (seasonStr[1] == 'a')
    seasonNum = 0;
  else if (seasonStr[1] == 'p')
    seasonNum = 1;
  else
    seasonNum = 2;
  return year * 3 - 6003 + seasonNum;
  */

  if (str[1] == 'a')
    return atoi(str + 5) * 3 - 6003;
  else if (str[1] == 'p')
    return atoi(str + 7) * 3 - 6002;
  else
    return atoi(str + 7) * 3 - 6001;

}
