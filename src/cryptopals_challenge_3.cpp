#include <iostream>
using namespace std;

char hexTable[16] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

int* binaryDividing(int totalNum, int* binaryValue, int arrayParamIndex) {
    int i = arrayParamIndex-1;
    do {
        binaryValue[i] = totalNum % 2;
        totalNum = totalNum / 2;
        i--;
    } while (totalNum > 0);
    if(i > -1) {
        for(i; i > -1; i--) {
            binaryValue[i] = 0;
        }
    }
    return binaryValue;
}

int binaryToDecimal(int binaryValue) {
    int decimal = 0, base = 1, rem;
    while(binaryValue > 0) {
        rem = binaryValue % 10;
        decimal = decimal + rem * base;
        binaryValue = binaryValue/10;
        base = base * 2;
    }
    return decimal;
}

int power(int value, int power) {
    if(power == 0) {
        return 1;
    }
    int originalValue = value;
    for(int i = 0;i < power-1;i++) {
        value = value * originalValue;
    }
    return value;
}

int getHexTableValue(char hex) {
    int i = 0;
    while(hexTable[i] != hex) {
        i++;
    }
    return i;
}

void printArray(int* arrayPtr, int length, int spaceCounterValue) {
    int spaceCounter = 0;
    for(int i = 0;i < length;i++) {
        cout << arrayPtr[i];
        spaceCounter++;
        if(spaceCounter == spaceCounterValue) {
            cout << ' ';
            spaceCounter = 0;
        }
    }
    cout << endl;
}

void printArray(char* arrayPtr, int length, int spaceCounterValue) {
    int spaceCounter = 0;
    for(int i = 0;i < length;i++) {
        cout << arrayPtr[i];
        spaceCounter++;
        if(spaceCounter == spaceCounterValue) {
            cout << ' ';
            spaceCounter = 0;
        }
    }
    cout << endl;
}

int* operationXOR(int* firstValueArray, int* secondValueArray, int size, int* responseArray) {
    for(int i = 0;i < size;i++) {
        if(firstValueArray[i] != secondValueArray[i]) {
            responseArray[i] = 1;
        } else {
            responseArray[i] = 0;
        }
    }
    cout << "\nresponseArray: ";
    printArray(responseArray,size,4);
    return responseArray;
}

int arrayToInt(int index, int* arrayPtr) {
    int responseNumber = 0;
    for(int i = index; i < index+4; i++) {
        responseNumber = responseNumber * 10 + arrayPtr[i];
    }
    return responseNumber;
}
int arrayToIntBytes(int index, int* arrayPtr) {
    int responseNumber = 0;
    for(int i = index; i < index+8; i++) {
        responseNumber = responseNumber * 10 + arrayPtr[i];
    }
    return responseNumber;
}

char* bruteForceXOR(int* firstValueArray, int size, char* responseArray) {
    char englishFrequency[26] = "ETAOIN SHRDLUetaoinshrdlu";
    char tmpArray[size/8];
    int englishCounter = 0, biggestEnglishCounter = 0;
    for(int i = 1; i < 256; i++) {
        int binaryValue[8];
        int arrayParamIndex = 8;
        binaryDividing(i,binaryValue,arrayParamIndex);
        int xorArray[size];
        int positionCounter = 0;
        for(int j = 0;j < size; j++) {
            if(firstValueArray[j] != binaryValue[positionCounter]) {
                xorArray[j] = 1;
            } else {
                xorArray[j] = 0;
            }
            positionCounter++;
            if(positionCounter == 8) {
                positionCounter = 0;
            }
        }
        // cout << "\n\nxorredArray: \n\n";
        // printArray(xorArray, size, 8);
        for(int k = 0; k < size/8; k++) {
            int binaryToInt = 0;
            if(k == 0) {
                binaryToInt = arrayToIntBytes(0, xorArray);
            } else {
                binaryToInt = arrayToIntBytes(k*8, xorArray);
            }
            // cout << "\n\nbinaryToInt\n\n" << binaryToInt;
            // cout << "\n\n size thing: \n\n" << k*8; 
            int binaryDecimal = binaryToDecimal(binaryToInt);
            tmpArray[k] = (char)binaryDecimal;
            for(int l = 0;l < 25;l++) {
                if((char)binaryDecimal == englishFrequency[l]) {
                    englishCounter++;
                    break;
                }
            }
            if(englishCounter > biggestEnglishCounter) {
                biggestEnglishCounter = englishCounter;
                for(int m = 0;m < size/8;m++) {
                    responseArray[m] = tmpArray[m];
                }
            }
       }
       englishCounter = 0; 
    }
    printArray(responseArray, size/8, 1000);
    return responseArray;
}


int* reverseIntArray(int* array, int length) {
    int size = length * 4;
    int tmpArray[size];
    int orderIndex = (length-1) * 4;
    int positionCounter = 0;
    for(int i = 0; i < size;i++) {
        tmpArray[i] = array[orderIndex];
        orderIndex++;
        positionCounter++;
        if(positionCounter == 4) {
            positionCounter = 0;
            orderIndex = orderIndex - 8;
        }
    }
    for(int i = 0; i < size; i++) {
        array[i] = tmpArray[i];
    }
    return array;
}

int main() {
    int length = 69, size = length*4;
    char xorEncryption[length] = "1B37373331363F78151B7F2B783431333D78397828372D363C78373E783A393B3736"; 
    int xorArray[size];
    for(int i = 0;i < length-1;i++) {
        int hexValue = getHexTableValue(xorEncryption[i]);
        int arrayParamIndex = size - i*4;
        binaryDividing(hexValue,&xorArray[0],arrayParamIndex);
    }
    reverseIntArray(xorArray, length);
    printArray(xorArray,size,8);
    char responseArray[size];
    bruteForceXOR(xorArray,size, responseArray);
    system("pause");
}













