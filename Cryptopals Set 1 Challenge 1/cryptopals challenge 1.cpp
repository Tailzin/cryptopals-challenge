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

int arrayToIntBytes(int index, int* arrayPtr) {
    int responseNumber = 0;
    for(int i = index; i < index+8; i++) {
        responseNumber = responseNumber * 10 + arrayPtr[i];
    }
    return responseNumber;
}

int arrayToIntBase64(int index, int* arrayPtr) {
    int responseNumber = 0;
    for(int i = index; i < index+6; i++) {
        responseNumber = responseNumber * 10 + arrayPtr[i];
    }
    return responseNumber;
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

int main() {
    char lookupTableBase64[64] = {
        'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z',
        'a','b','c','d','e','f','g','h','i','j','k','l','m','n','o','p','q','r','s','t','u','v','w','x','y','z',
        '0','1','2','3','4','5','6','7','8','9','+','/'};    
    char inputToConvertBuffer[1000];
    cout << "Type string to convert: \n";
    cin >> inputToConvertBuffer;
    int length;
    while(inputToConvertBuffer[length] != '\0') {
        length++;
    }
    inputToConvertBuffer[length] = (char)10;
    inputToConvertBuffer[length+1] = '0';
    length++;
    cout << "Length: " << length << endl;
    int size = 8*length;
    int array[size];
    int* arrayPtr = array;
    char inputToConvert[length+1];
    for(int i = 0; i < length;i++) {
        inputToConvert[i] = inputToConvertBuffer[i];
    }
    for(int i = 0; i < length; i++) {
        int charToInt;
        if((int)inputToConvert[i] > 47 && (int)inputToConvert[i] < 58 || (int)inputToConvert[i] == 10) {
            charToInt = (int)inputToConvert[i];
            cout << "ASCII code of " << inputToConvert[i] << ": " << charToInt << "\n";
        } else if ((int)inputToConvert[i] > 96 && (int)inputToConvert[i] < 123){
            charToInt = (int)inputToConvert[i]-32;
            inputToConvert[i] = (char)charToInt;
            cout << "ASCII code of " << (char)charToInt << ": " << charToInt << "\n";
        } else {
            charToInt = (int)inputToConvert[i];
            cout << "ASCII code of " << inputToConvert[i] << ": " << charToInt << "\n";            
        }
        int arrayParamIndex = size - i*8;
        arrayPtr = binaryDividing(charToInt, arrayPtr, arrayParamIndex);
    }
    int spaceCounter = 0;
    int orderedArray[size]; 
    int orderIndex = (length - 1) * 8;
    int positionCounter = 0;
    for(int i = 0;i < size;i++) {
        orderedArray[i] = array[orderIndex];
        orderIndex++;
        positionCounter++;
        if(positionCounter == 8) {
            orderIndex = orderIndex - 16;
            positionCounter = 0;
        }
    }

    for(int i = 0; i < size;i++) {
        cout << orderedArray[i];
        spaceCounter++;
        if(spaceCounter == 8) {
            cout << " ";
            spaceCounter = 0;
        }
    }
    cout << endl;
    int decimalArraySize = size/8;
    int decimalArray[decimalArraySize];
    for(int i = 0; i < decimalArraySize;i++) {
        int binaryValue;
        if(i == 0) { 
            binaryValue = arrayToIntBytes(0, &orderedArray[0]);
        } else {
            binaryValue = arrayToIntBytes(i*8, &orderedArray[0]);  
        }
        decimalArray[i] = binaryToDecimal(binaryValue);
        cout << decimalArray[i] << " ";
    }
    cout << endl;

    int base64OrderedArraySize;
    if(size % 6 != 0) {
        base64OrderedArraySize = size + (6-(size%6));
    } else {
        base64OrderedArraySize = size;
    }
    int base64OrderedArray[base64OrderedArraySize];
    int base64DecimalArraySize;
    if((base64OrderedArraySize/6) % 4 != 0) {
        base64DecimalArraySize = (base64OrderedArraySize/6) + (4 - ((base64OrderedArraySize/6) % 4));
    }
    int base64DecimalArray[base64DecimalArraySize];
    for(int i = 0; i < base64OrderedArraySize; i++) {
        if(i > size-1) {
            base64OrderedArray[i] = 0;
        }
        else {
            base64OrderedArray[i] = orderedArray[i];
        }
    }
    char base64String[base64DecimalArraySize];
    cout << "Text to base64: ";
    for(int i = 0; i < base64DecimalArraySize;i++) {
        int binaryValue;
        if(i == 0) {
            binaryValue = arrayToIntBase64(0, &base64OrderedArray[0]);
        } else if(i>= (base64OrderedArraySize/6)) {
            binaryValue = 00111101;
        } else {
            binaryValue = arrayToIntBase64(i*6, &base64OrderedArray[0]);
        }
        base64DecimalArray[i] = binaryToDecimal(binaryValue);
        if(binaryValue == 00111101) {
            base64String[i] = '=';
        } else {
            base64String[i] = lookupTableBase64[base64DecimalArray[i]];
        }
        cout << base64String[i];
    }
    cout << endl;
    if((length-1) % 2 == 0) {
        inputToConvertBuffer[length-1] = '\0';
        length--;
    }
    size = length*4;
    int hexBinaryArray[size];
    int* hexBinaryArrayPtr = hexBinaryArray;
    for(int i = 0;i < length;i++) {
        int arrayParamIndex = size - i*4;        
        if((int)inputToConvert[i] != 10) {
            cout << "HEX: " << getHexTableValue(inputToConvert[i]) << " ";
            hexBinaryArrayPtr = binaryDividing(getHexTableValue(inputToConvert[i]), hexBinaryArrayPtr, arrayParamIndex);
        }
    }
    cout << endl;
    spaceCounter = 0;
    int hexOrderedArray[size]; 
    orderIndex = (length-1) * 4;
    positionCounter = 0;
    cout << "Order Index: " << orderIndex << endl;
    for(int i = 0;i < size;i++) {
        hexOrderedArray[i] = hexBinaryArray[orderIndex];
        orderIndex++;
        positionCounter++;
        if(positionCounter == 4) {
            orderIndex = orderIndex - 8;
            positionCounter = 0;
        }
    }    
    for(int i = 0; i < size;i++) {
        cout << hexOrderedArray[i];
        spaceCounter++;
        if(spaceCounter == 4) {
            cout << " ";
            spaceCounter = 0;
        }
    }
    cout << endl; 
    int hexBase64OrderedArraySize;
    if(size % 6 != 0) {
        hexBase64OrderedArraySize = size + (6-(size%6));
    } else {
        hexBase64OrderedArraySize = size;
    }
    int hexBase64OrderedArray[hexBase64OrderedArraySize];
    int hexBase64DecimalArraySize;
    // size = (length-1)*4;
    // if(size % 6 != 0) {
    //     hexBase64OrderedArraySize = size + (6-(size%6));
    // } else {
    //     hexBase64OrderedArraySize = size;
    // }    
    if((hexBase64OrderedArraySize/6) % 4 != 0) {
        hexBase64DecimalArraySize = (hexBase64OrderedArraySize/6) + (4 - ((hexBase64OrderedArraySize/6) % 4));
    } else {
        hexBase64DecimalArraySize = hexBase64OrderedArraySize/6;
    }
    cout << "hexBase64DecimalArraySize: " << hexBase64DecimalArraySize << "\nhexBase64OrderedArraySize: " << hexBase64OrderedArraySize << endl;
    int hexBase64DecimalArray[hexBase64DecimalArraySize];
    cout << "Base64 Binary: ";
    spaceCounter = 0;
    for(int i = 0; i < hexBase64OrderedArraySize; i++) {
        if(i > size-1) {
            hexBase64OrderedArray[i] = 0;
        }
        else {
            hexBase64OrderedArray[i] = hexOrderedArray[i];
        }
        cout << hexBase64OrderedArray[i];
        spaceCounter++;
        if(spaceCounter == 6) {
            cout << ' ';
            spaceCounter = 0;
        }
    }
    cout << endl;
    char hexBase64String[hexBase64DecimalArraySize];
    cout << "Hex to base64: ";
    for(int i = 0; i < hexBase64DecimalArraySize;i++) {
        int binaryValue;
        if(i == 0) {
            binaryValue = arrayToIntBase64(0, &hexBase64OrderedArray[0]);
        } else if(i>= (hexBase64OrderedArraySize/6)) {
            binaryValue = 00111101;
        } else {
            binaryValue = arrayToIntBase64(i*6, &hexBase64OrderedArray[0]);
        }
        hexBase64DecimalArray[i] = binaryToDecimal(binaryValue);
        if(binaryValue == 00111101) {
            hexBase64String[i] = '=';
        } else {
            hexBase64String[i] = lookupTableBase64[hexBase64DecimalArray[i]];
        }
        cout << hexBase64String[i];
    }
    cout << endl;
    system("pause"); 
}
