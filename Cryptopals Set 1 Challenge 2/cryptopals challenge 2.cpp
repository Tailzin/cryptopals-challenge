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

int hexToDecimal(char* hex, int hexSize) {
    int counter = hexSize;
    int sum = 0;
    for(int i = 0;i < hexSize;i++) { 
        int hexValue = getHexTableValue(hex[i]);
        counter--;
        sum = sum + hexValue * (power(16,counter));
    }
    return sum;
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

char* encodeXOR(char* fixedXORValue1, char* fixedXORValue2, char* xorResponseArray) {
    int length = 36;
    int size = length*4;
    int binaryArrayValue1[size];
    int* binaryArrayValue1Ptr = binaryArrayValue1;
    int binaryArrayValue2[size];
    int* binaryArrayValue2Ptr = binaryArrayValue2;
    int xorArray[size];
    int* xorArrayPtr = xorArray; 
    for(int i = 0;i < length;i++) {
        int charToInt = (int)fixedXORValue1[i];
        if(charToInt > 96 && charToInt < 123) {
            charToInt = charToInt - 32;
            fixedXORValue1[i] = (char)charToInt;
        }
        charToInt = (int)fixedXORValue2[i];
        if(charToInt > 96 && charToInt < 123) {
            charToInt = charToInt - 32;
            fixedXORValue2[i] = (char)charToInt;
        }
    }
    cout << fixedXORValue1 << "\n" << fixedXORValue2 << "\n";
    for(int i = 0; i < length; i++) {
        int hexInt = getHexTableValue(fixedXORValue1[i]);
        // int hexInt = (int)fixedXORValue1[i];
        int arrayParamIndex = size - i*4;
        // cout << arrayParamIndex << "\n";
        binaryArrayValue1Ptr = binaryDividing(hexInt, binaryArrayValue1Ptr, arrayParamIndex);  
    }

    for(int i = 0; i < length; i++) {
        int hexInt = getHexTableValue(fixedXORValue2[i]);
        // int hexInt = (int)fixedXORValue2[i];
        int arrayParamIndex = size - i*4;
        binaryArrayValue2Ptr = binaryDividing(hexInt, binaryArrayValue2Ptr, arrayParamIndex);      
    }

    int binaryArrayValue1Ordered[size];
    int binaryArrayValue2Ordered[size];
    int orderIndex = (length-1) * 4;
    int positionCounter = 0;


    for(int i = 0;i < size; i++) {
        binaryArrayValue1Ordered[i] = binaryArrayValue1[orderIndex];
        orderIndex++;
        positionCounter++;
        if(positionCounter == 4) {
            orderIndex = orderIndex - 8;
            positionCounter = 0;
        }
    }

    orderIndex = (length-1) * 4;
    positionCounter = 0;
    for(int i = 0;i < size; i++) {
        binaryArrayValue2Ordered[i] = binaryArrayValue2[orderIndex];
        orderIndex++;
        positionCounter++;
        if(positionCounter == 4) {
            orderIndex = orderIndex - 8;
            positionCounter = 0;
        }
    }


    cout << "\nBinaryArrayValue1Ordered: ";
    printArray(&binaryArrayValue1Ordered[0], size, 4);
    cout << "\nBinaryArrayValue2Ordered: ";
    printArray(&binaryArrayValue2Ordered[0], size, 4);

    xorArrayPtr = operationXOR(binaryArrayValue1Ordered, binaryArrayValue2Ordered,size, xorArrayPtr);
    int responseCounter = 0;
    int counter = 0;
    for(int i = 0;i < size;i++) {
        int binaryToInt[4];
        int binaryToIntValue = 0, decimalValue = 0;
        binaryToInt[counter] = xorArrayPtr[i];
        counter++;
        if(counter == 4) {
            counter = 0;
            binaryToIntValue = arrayToInt(0, &binaryToInt[0]);
            decimalValue = binaryToDecimal(binaryToIntValue);
            cout << hexTable[decimalValue];
            xorResponseArray[responseCounter] = hexTable[decimalValue];
            responseCounter++;
        }
    }
    cout << endl;
    return &xorResponseArray[0];
}

int main() {
    int length = 36;
    char fixedXORValue1[length], fixedXORValue2[length];
    cout << "Type value 1: ";
    cin >> fixedXORValue1;
    cout << "\nType value 2: ";
    cin >> fixedXORValue2;
    cout << endl;
    char xorResponseArray[length];
    encodeXOR(&fixedXORValue1[0], &fixedXORValue2[0], &xorResponseArray[0]);
    printArray(xorResponseArray, length, 100);
    system("pause");
}