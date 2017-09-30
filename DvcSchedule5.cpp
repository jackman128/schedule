//Programmer: Jack Wilson
//Programmer ID: 1617227

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

#include <cstring>
#include "DynamicArray.h"

//This struct holds the number of sections offered for each subject.
struct SectionsForSubject
{
  string subjectCode;
  int numSections = 0;
};

//This struct holds an array of section numbers that correspond to a term.
struct SectionsForTerm
{
  int sectionsSeen = 0;
  //section codes are always 4 digits, so 'short' should be big enough.
  DynamicArray<short> seenSectionNumber;
};

//This function maps a term string ("Fall 2007") to an index for 'alreadySeen'.
//It does this because jumping to a location in alreadySeen is much faster
//than doing a linear search for a term string.
size_t termToIndex(const string &str);

//This is the name of the input file.
const string fileName = "dvc-schedule.txt";

int main()
{
  //output student information
  cout << "Programmer: Jack Wilson" << endl;
  cout << "Programmer ID: 1617227" << endl;
  cout << "File: " << __FILE__ << endl;
  cout << endl;


  //open the input file and throw an exception if it's unsuccessful
  ifstream fin;
  fin.open(fileName);
  if (!fin.good()) throw "I/O error";

  //subjectCodes: holds the number of sections for each subject.
  DynamicArray<SectionsForSubject> subjectCodes(150);

  //alreadySeen: holds arrays full of section numbers for each term
  //in order to keep track of duplicates.
  DynamicArray<SectionsForTerm> alreadySeen(100);

  //numSubjectCodes: number of unique subject codes, like "MATH" or "ENGL"
  int numSubjectCodes = 0;
  //duplicates: number of duplicates counted so far
  int duplicates= 0;
  //line: the current line being parsed from the input file
  string line;
  //token: points to a position in buf
  char* token;
  //buf: holds a portion of the input file for parsing
  char buf[1000];
  const char* const tab = "\t";
  while (fin.good()) {
    // read the line
    getline(fin, line);
    strcpy(buf, line.c_str());

    if (buf[0] == 0) continue; // skip blank lines

    //parse the line
    const string term(token = strtok(buf, tab));
    const string section((token = strtok(0, tab)) ? token : "");
    const string course((token = strtok(0, tab)) ? token : "");
    const string instructor((token = strtok(0, tab)) ? token : "");
    const string whenWhere((token = strtok(0, tab)) ? token : "");
    if (course.find('-') == string::npos) continue; // invalid line: no dash in course name
    const string subjectCode(course.begin(), course.begin() + course.find('-'));


    //DEDUP
    bool isDup = false;
    size_t index = termToIndex(term); //convert term to an index in sectionsSeen
    short sectionShort = static_cast<short>(stoi(section)); //convert section to a short
    //loop over section numbers in the corresponding SectionsForTerm in 'alreadySeen'
    //until a duplicate is found
    for (int i = 0; i < alreadySeen[index].sectionsSeen; i++) {
      if (sectionShort == alreadySeen[index].seenSectionNumber[i]) {
        isDup = true;
        duplicates++;
        break;
      }
    }
    //If it's a duplicate, skip to the next line in the file.
    if (isDup) {
      continue;
    }
    else {
      //If it's not a duplicate, insert this section number
      //into the corresponding SectionsForTerm.
      int i = alreadySeen[index].sectionsSeen++;
      alreadySeen[index].seenSectionNumber[i] = sectionShort;
    }

    //COUNT
    //Find the matching subject code for the course that is currently being looked at
    //and increment the counter for that subject code.
    int j = 0;
    for (; j < numSubjectCodes; j++) {
      if (subjectCodes[j].subjectCode == subjectCode) {
        //subject code for this course matches an existing subject code
        subjectCodes[j].numSections++;
        break;
      }
    }
    //if the end of the previous loop was reached, then this is a subject code
    //that hasn't been seen before. Insert it into subjectCodes and increment
    //numSubjectCodes.
    if (j == numSubjectCodes) {
      subjectCodes[j].subjectCode = subjectCode;
      subjectCodes[j].numSections++;
      numSubjectCodes++;
    }
  }
  //Close the file, it's not being read anymore.
  fin.close();

  //Use insertion sort to sort the subject codes into alphabetical order.
  int i = 1;
  while (i < numSubjectCodes) {
    SectionsForSubject t = subjectCodes[i];
    int j = i - 1;
    while (j >= 0 && subjectCodes[j].subjectCode > t.subjectCode) {
      subjectCodes[j + 1] = subjectCodes[j];
      j--;
    }
    subjectCodes[j + 1] = t;
    i++;
  }

  //Now print out the number of unique subject codes,
  //each subject code with the number of sections,
  //and the number of duplicates found.
  cout << endl;
  cout << "Subject codes: " << numSubjectCodes << endl;
  for (int i = 0; i < numSubjectCodes; i++) {
    cout << subjectCodes[i].subjectCode <<": " << subjectCodes[i].numSections << endl;
  }
  cout << endl;
  cout << "Duplicates: " << duplicates << endl;

  return 0;
}

size_t termToIndex(const string &str)
{
  //Each term string has a season (Fall, Spring, or Summer)
  //and a year, separated by a space.
  string seasonStr = str.substr(0, str.find(" "));
  string year = str.substr(str.find(" "));

  int seasonNum;
  if (seasonStr == "Fall")
    seasonNum = 0;
  else if (seasonStr == "Spring")
    seasonNum = 1;
  else
    seasonNum = 2;

  //The year is multiplied by three to "make room" for the seasonNum.
  //Subtract by 6003 to make "Fall 2001" the 0th index.
  return stoi(year) * 3 + seasonNum - 6003;
}
