#include <iostream>
#include "libs/cryptoutils.h"

using namespace std;

int hammingDistance(int firstValue[], int secondValue[], int size) {
    int differenceCounter = 0;
    for(int i = 0;i < size;i++) {
        if(firstValue[i] != secondValue[i]) {
            differenceCounter++;
        }
    }
    return differenceCounter;
}

int main() {
    int firstStringLength = 15, secondStringLength = 15, firstStringSize = (firstStringLength-1)*8, secondStringSize = (secondStringLength-1)*8;
    char firstString[firstStringLength] = "this is a test";
    char secondString[secondStringLength] = "wokka wokka!!!";
    int firstStringBinary[firstStringSize];
    int secondStringBinary[secondStringSize];
    binaryDividing(firstStringBinary, 8, firstString);
    binaryDividing(secondStringBinary, 8, secondString);
    cout << "First string binary: ";
    printArray(firstStringBinary, firstStringSize, 8);
    cout << "\nSecond string binary: ";
    printArray(secondStringBinary, secondStringSize, 8);
    cout << hammingDistance(firstStringBinary, secondStringBinary,firstStringSize) << endl;

    system("pause");
    return 0;
}