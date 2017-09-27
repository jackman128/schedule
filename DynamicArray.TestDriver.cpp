//Programmer: Jack Wilson
//Programmer ID: 1617227

#include <iostream>
#include <string>

using namespace std;

#include <cassert> //for assert()
#include <vector>

#include "DynamicArray.h"
#include "DynamicArray.h" //Include guard test


int main()
{
    cout << "Programmer: Jack Wilson" << endl;
    cout << "Programmer ID: 1617227" << endl;
    cout << "File: " << __FILE__ << endl;
    cout << endl;
    cout << "dither";

    DynamicArray<char> charArray;

    cout << "PART 1: Test DynamicArray of chars." << endl;

    cout << "Test #1: Test Capacity() setter" << endl;
    charArray.Capacity(100);
    assert(charArray.Capacity() == 100);
    cout << "Passed." << endl << endl;

    cout << "Test #2: Make sure that all initial values are the default value." << endl;
    for (int i = 0; i < charArray.Capacity(); i++)
    {
        assert(charArray[i] == char());
    }
    cout << "Passed." << endl << endl;

    cout << "Test #3: Make sure that the array getter and setter work." << endl;
    //create test vectors to hold values and the indices that they will be held at.
    vector<char> charValues = {'a', '|', ')', '0', 'Q', '!'};
    vector <int> charIndices = {15, 100, 64, 3, 6, 80};
    //set the indices in charArray to the corresponding test values
    for (int i = 0; i < charIndices.capacity(); i++) {
        charArray[charIndices[i]] = charValues[i];
    }
    //read the values back to make sure that the getter and setter work correctly.
    for (int i = 0; i < charIndices.capacity(); i++) {
        cout << "Expected value for index " << charIndices[i] << ": "
            << charValues[i] << endl;
        cout << "Actual: " << charArray[charIndices[i]] << endl;
        assert(charValues[i] == charArray[charIndices[i]]);
    }
    cout << "Passed." << endl << endl;

    const DynamicArray<char> constcharArray = charArray;

    cout << "Test #4: 'const' test Capacity getter" << endl;
    assert(constcharArray.Capacity() == charArray.Capacity());
    cout << "Passed." << endl << endl;

    cout << "Test #5: 'const' test bracket getter." << endl;
    for (int i = 0; i < charArray.Capacity(); i++)
    {
        assert(constcharArray[i] == charArray[i]);
    }
    cout << "Passed." << endl << endl;

    cout << "Test #6: Test the copy constructor" << endl;
    DynamicArray<char> copyCharArray = charArray;
    for (int i = 0; i < charArray.Capacity(); i++) {
        assert(copyCharArray[i] == charArray[i]);
    }
    cout << "Passed." << endl << endl;

    cout << "Test #7: Test the assignment operator" << endl;
    DynamicArray<char> assignCharArray;
    assignCharArray = charArray;
    for (int i = 0; i < charArray.Capacity(); i++) {
        assert(assignCharArray[i] == charArray[i]);
    }
    cout << "Passed." << endl << endl;

    cout << "PART 2: Test DynamicArray of strings." << endl;

    DynamicArray<string> stringArray;

    cout << "Test #1: Test Capacity() setter" << endl;
    stringArray.Capacity(100);
    assert(stringArray.Capacity() == 100);
    cout << "Passed." << endl << endl;

    cout << "Test #2: Make sure that all initial values are the default value." << endl;
    for (int i = 0; i < stringArray.Capacity(); i++)
    {
        assert(stringArray[i] == string());
    }
    cout << "Passed." << endl << endl;

    cout << "Test #3: Make sure that the array getter and setter work." << endl;

    //create test vectors to hold test values
    vector<string> stringValues = {"Hello", "Hi,\nthere!", "TEST", "_____"};
    vector <int> stringIndices = {24, 81, 0, 99};
    for (int i = 0; i < stringIndices.capacity(); i++) {
        stringArray[stringIndices[i]] = stringValues[i];
    }
    for (int i = 0; i < stringIndices.capacity(); i++) {
        cout << "Expected value for index " << stringIndices[i] << ": "
            << stringValues[i] << endl;
        cout << "Actual: " << stringArray[stringIndices[i]] << endl;
        assert(stringValues[i] == stringArray[stringIndices[i]]);
    }
    cout << "Passed." << endl << endl;

    const DynamicArray<string> conststringArray = stringArray;

    cout << "Test #4: 'const' test Capacity()" << endl;
    assert(conststringArray.Capacity() == stringArray.Capacity());
    cout << "Passed." << endl << endl;

    cout << "Test #5: 'const' test the getter." << endl;
    for (int i = 0; i < stringArray.Capacity(); i++)
    {
        assert(conststringArray[i] == stringArray[i]);
    }
    cout << "Passed." << endl << endl;

    cout << "Test #6: Test the copy constructor" << endl;
    DynamicArray<string> copystringArray = stringArray;
    for (int i = 0; i < stringArray.Capacity(); i++) {
        assert(copystringArray[i] == stringArray[i]);
    }
    cout << "Passed." << endl << endl;

    cout << "Test #7: Test the assignment operator" << endl;
    DynamicArray<string> assignstringArray;
    assignstringArray = stringArray;
    for (int i = 0; i < stringArray.Capacity(); i++) {
        assert(assignstringArray[i] == stringArray[i]);
    }
    cout << "Passed." << endl << endl;

}
