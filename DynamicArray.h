#ifndef DYNAMICARRAY_H_INCLUDED
#define DYNAMICARRAY_H_INCLUDED

#include <cmath> //for abs()

template <typename T>
class DynamicArray
{
    private:
        //points to the array
        T* array;
        //dummy value is returned on an invalid access
        T dummy;
        //cap is the capacity
        int cap;

    public:

//main constructor: initializes values.
//The default capacity is 2.
DynamicArray(int cap = 2)
{
    //the value of dummy doesn't matter
    this->dummy = T();
    //set the capacity
    this->cap = cap;
    //allocate memory to hold the array.
    this->array = new T[cap];
    //set all values in the array to the default value
    for (int i = 0; i < cap; i++) {
        this->array[i] = T();
    }
}

//Copy constructor: copies all elements over to the
//new object, except for dummy
DynamicArray(const DynamicArray<T> &original)
{
    this->dummy = T();
    this->cap = original.cap;
    this->array = new T[original.cap];
    //copy contents of original array to the new one.
    for (int i = 0; i < original.cap; i++) {
        this->array[i] = original.array[i];
    }
}

//assignment operator: If the two arrays are not the same,
//then perform the same thing as the copy constructor, then return a reference.
//otherwise, just return a reference to itself.
DynamicArray<T> operator=(const DynamicArray<T> &original)
{
    if (this != &original) {
        delete[] array;

        this->dummy = T();
        this->cap = original.cap;
        this->array = new T[original.cap];
        for (int i = 0; i < original.cap; i++) {
            this->array[i] = original.array[i];
        }
    }
    return *this;
}

//Destructor: delete the contents of the array
~DynamicArray()
{
    delete[] array;
}

//Capacity getter: return the current capacity
int Capacity() const
{
    return cap;
}

//Capacity setter: set the new capacity and move all array elements
//to a new array with the proper size.
void Capacity(int newCapacity)
{
    T* newArray = new T[newCapacity];

    //in the first loop, go from zero to the lesser of newCapacity or cap.
    //this ensures that we stay within the bounds of the original array.
    int loopLength = (newCapacity < this->cap) ? (newCapacity) : (this->cap);
    for (int i = 0; i < loopLength; i++) {
        newArray[i] = this->array[i];
    }
    for (int i = loopLength; i < newCapacity; i++) {
        newArray[i] = T();
    }
    delete[] array;
    array = newArray;
    cap = newCapacity;
}

//operator[] getter: return the element indicated.
//If the index is invalid, return dummy
T operator[](int index) const
{
    if (index < 0 || index >= cap)
        return dummy;
    return array[index];
}

//operator[] setter: return a reference to the element indicated.
//If the index is negative, return dummy.
//If the index is greater than the current capacity, adjust the capacity
//and then return a reference to the indicated element.
T& operator[](int index)
{
    if (index < 0) {
        return dummy;
    }
    if (index >= cap) {
        Capacity(index * 2);
        return array[index];
    }
    return array[index];
}

};



#endif // DYNAMICARRAY_H_INCLUDED
