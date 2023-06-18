#include <iostream>

char hexTable[17] = "0123456789ABCDEF";

void hexDividing(char* hexArray, int decimalArray[], int size) {
    int index = 0;
    //starts from last letter so binary array will be in correct order
    for(int i = 0;i < size;i++) {
        int hexNum = decimalArray[i];
        if(hexNum > 15) {
            while(hexNum > 0) {
                hexArray[index] = hexTable[hexNum%16];
                hexNum = hexNum/16;
                index++;
            }
            char tmp = hexArray[index-1];
            hexArray[index-1] = hexArray[index-2];
            hexArray[index-2] = tmp;
        } else {
            hexArray[index] = '0';
            index++;
            hexArray[index] = hexTable[hexNum];
            index++;
        }
    }
}


void binaryDividing(int* binaryArray, int numberOfBits, char string[]) {
    int length = 0;
    while(string[length] != '\0') {
        length++;
    }
    // subtract because array starts at 0
    int index = length*numberOfBits-1;
    //starts from last letter so binary array will be in correct order
    for(int i = length-1;i >= 0;i--) {
        int totalNum = (int)string[i];
        int endOfValue = index - numberOfBits;
        while(totalNum > 0) {
            binaryArray[index] = totalNum%2;
            totalNum = totalNum/2;
            index--;
        }
        if(index > endOfValue) {
            for(int j = index;j > endOfValue;j--) {
                binaryArray[j] = 0;
                index--;
            }
        }
    }
}

void printArray(int* arrayPtr, int length, int spaceCounterValue) {
    int spaceCounter = 0;
    for(int i = 0;i < length;i++) {
        std::cout << arrayPtr[i];
        spaceCounter++;
        if(spaceCounter == spaceCounterValue) {
            std::cout << ' ';
            spaceCounter = 0;
        }
    }
    std::cout << std::endl;
}

void printArray(char* arrayPtr, int length, int spaceCounterValue) {
    int spaceCounter = 0;
    for(int i = 0;i < length;i++) {
        std::cout << arrayPtr[i];
        spaceCounter++;
        if(spaceCounter == spaceCounterValue) {
            std::cout << ' ';
            spaceCounter = 0;
        }
    }
    std::cout << std::endl;
}

void binaryArrayToInt(int* resultArray, int binaryArray[], int size, int numberOfBits) {
    for(int i = 0; i < size;i++) {
        int counterPosition = i*numberOfBits;
        int responseNumber = 0;
        for(int j = counterPosition; j < counterPosition+numberOfBits;j++) {
            responseNumber = responseNumber * 10 + binaryArray[j]; 
        }
        resultArray[i] = responseNumber;
    }
}

void binaryToDecimal(int* resultArray, int binaryArray[], int size) {
    for(int i = 0; i < size;i++) {
    int decimal = 0, base = 1, remainder, currentValue = binaryArray[i];
        while(currentValue > 0) {
            remainder = currentValue % 10;
            decimal = decimal + remainder * base;
            currentValue = currentValue / 10;
            base = base * 2;
        }
        resultArray[i] = decimal;
    }
}
