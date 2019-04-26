#include <iostream>
#include <string.h>

#include "Aes.h"

using namespace std;

const int Aes::rcon[10] = { 0x01000000, 0x02000000,
                            0x04000000, 0x08000000,
                            0x10000000, 0x20000000,
                            0x40000000, 0x80000000,
                            0x1b000000, 0x36000000 };
const int Aes::S[16][16] = {0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
                            0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
                            0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
                            0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
                            0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
                            0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
                            0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
                            0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
                            0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
                            0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
                            0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
                            0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
                            0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
                            0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
                            0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
                            0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 };
const int Aes::S2[16][16] = {0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
                            0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
                            0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
                            0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
                            0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
                            0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
                            0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
                            0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
                            0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
                            0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
                            0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
                            0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
                            0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
                            0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
                            0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
                            0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d };
const int Aes::colM[4][4] = {2, 3, 1, 1,
                            1, 2, 3, 1,
                            1, 1, 2, 3,
                            3, 1, 1, 2 };
const int Aes::deColM[4][4] = { 0xe, 0xb, 0xd, 0x9,
                            0x9, 0xe, 0xb, 0xd,
                            0xd, 0x9, 0xe, 0xb,
                            0xb, 0xd, 0x9, 0xe };
Aes::Aes(){}
Aes::~Aes(){}

void Aes::encrypt(char *p, int len, char *key){
    if(len % 16 != 0){
        cout << "len error!" << endl;
        return;
    }
    if(strlen(key) % 16 != 0){
        cout << "key lenth error!" << endl;
        return;
    }

    extendKey(key);

    int arr[4][4];
    for(int i = 0; i < len; i += 16){

        convertToIntArray(p+i, arr);

        addRoundKey(arr, 0);
        for(int j = 1; j < 10; j++){
            subBytes(arr);
            shiftRows(arr);
            mixColumns(arr);
            addRoundKey(arr, j);
        }
        subBytes(arr);
        shiftRows(arr);
        addRoundKey(arr, 10);
        convertArrayToStr(arr, p+i);
    }
}

void Aes::decrypt(char *p, int len, char *key){
    extendKey(key);

    int arr[4][4];
    for(int i = 0; i < len; i += 16){

        convertToIntArray(p + i, arr);
        addRoundKey(arr, 10);

        int wArray[4][4];
        for(int j = 9; j >= 1; j--){
            deSubBytes(arr);
            deShiftRows(arr);
            deMixColumns(arr);
			getArrayFrom4W(j, wArray);
			deMixColumns(wArray);
            addRoundTowArray(arr, wArray);
        }
        deSubBytes(arr);

		deShiftRows(arr);

		addRoundKey(arr, 0);

		convertArrayToStr(arr, p + i);
    }
}

void Aes::extendKey(char *key){
    for(int i = 0; i < 4; i++){
        w[i] = getWordFromStr(key + i*4);
    }
    int j = 0;
    for(int i = 4; i < 44; i++){
        if(i % 4 == 0){
            w[i] = w[i-4] ^ T(w[i-1], j);
            j++;
        }else{
            w[i] = w[i-4] ^ w[i-1];
        }
    }
}

int Aes::getWordFromStr(char *key){
    int one = getIntFromChar(key[0]);
    one = one << 24;
    int two = getIntFromChar(key[1]);
    two = two << 16;
    int three = getIntFromChar(key[2]);
    three = three << 8;
    int four = getIntFromChar(key[3]);
    return one | two | three | four;
}

int Aes::getIntFromChar(char key){
    int result = key;
    return result & 0x000000ff; 
}

int Aes::T(int w, int j){
    int numArr[4];
    splitIntToArray(w, numArr);
    leftLoop4int(numArr, 1);

    for(int i = 0; i < 4; i++){
        numArr[i] = getNumFromSBox(numArr[i]);
    }
    int result = mergeArrayToInt(numArr);
    return result ^ rcon[j];
}

void Aes::splitIntToArray(int w, int arr[4]){
    arr[0] = (w >> 24) & 0x000000ff;
    arr[1] = (w >> 16) & 0x000000ff;
    arr[2] = (w >> 8) & 0x000000ff;
    arr[3] = w & 0x000000ff;
}

void Aes::leftLoop4int(int arr[4], int step){
    int temp[4];
    for(int i = 0; i < 4; i++){
        temp[i] = arr[i];
    }
    int index = step % 4;
    for(int i = 0; i < 4; i++){
        arr[i] = temp[index];
        ++index %= 4;
    }
}

int Aes::getNumFromSBox(int num){
    int row = (num & 0x000000f0) >> 4;
    int col = num & 0x0000000f;
    return S[row][col];
}

int Aes::mergeArrayToInt(int arr[4]){
    int one = arr[0] << 24;
    int two = arr[1] << 16;
    int three = arr[2] << 8;
    int four = arr[3];
    return one | two | three | four;
}

void Aes::convertToIntArray(char *p, int arr[4][4]){
    int k = 0;
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            arr[j][i] = getIntFromChar(p[k]);
            k++;
        }
    }
}

void Aes::addRoundKey(int arr[4][4], int round){
    int wArr[4];
    for(int i = 0; i < 4; i++){
        splitIntToArray(w[round*4 + i], wArr);

        for(int j = 0; j < 4; j++){
            arr[j][i] ^= wArr[j];
        }
    }
}

void Aes::subBytes(int arr[4][4]){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            arr[i][j] = getNumFromSBox(arr[i][j]);
        }
    }
}

void Aes::shiftRows(int arr[4][4]){
    int *p2 = arr[1];
    int *p3 = arr[2];
    int *p4 = arr[3];

    leftLoop4int(p2, 1);
    leftLoop4int(p3, 2);
    leftLoop4int(p4, 3);
}

int Aes::GFMul2(int s){
    int result = s << 1;
    int a7 = result & 0x00000100;
    if(a7 != 0){
        result &= 0x000000ff;
        result ^= 0x1b;
    }
    return result;
}

int Aes::GFMul3(int s){
    return GFMul2(s) ^ s;
}

int Aes::GFMul4(int s) {
	return GFMul2(GFMul2(s));
}

int Aes::GFMul8(int s) {
	return GFMul2(GFMul4(s));
}

int Aes::GFMul9(int s) {
	return GFMul8(s) ^ s;
}

int Aes::GFMul11(int s) {
	return GFMul9(s) ^ GFMul2(s);
}

int Aes::GFMul12(int s) {
	return GFMul8(s) ^ GFMul4(s);
}

int Aes::GFMul13(int s) {
	return GFMul12(s) ^ s;
}

int Aes::GFMul14(int s) {
	return GFMul12(s) ^ GFMul2(s);
}

int Aes::GFMul(int n, int s){
    int result;
    if(n == 1){
        result = s;
    }else if(n == 2){
        result = GFMul2(s);
    }else if(n == 3){
        result = GFMul3(s);
    }else if(n == 0x9){
        result = GFMul9(s);
    }else if(n == 0xb){
        result = GFMul11(s);
    }else if(n == 0xd){
        result = GFMul13(s);
    }else if(n == 0xe){
		result = GFMul14(s);
    }    
    return result;
}

void Aes::mixColumns(int arr[4][4]){
    int temp[4][4];
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            temp[i][j] = arr[i][j];
        }
    }
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            arr[i][j] = GFMul(colM[i][0], temp[0][j]) ^ GFMul(colM[i][1], temp[1][j]) 
            ^ GFMul(colM[i][2], temp[2][j]) ^ GFMul(colM[i][3], temp[3][j]);
        }
    }
}

void Aes::convertArrayToStr(int arr[4][4], char *p){
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            *p++ = (char)arr[j][i];
        }
    }
}

void Aes::deSubBytes(int arr[4][4]){
    for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			arr[i][j] = getNumFromS1Box(arr[i][j]);
}

int Aes::getNumFromS1Box(int num){
    int row = (num & 0x000000f0) >> 4;
    int col = num & 0x0000000f;
    return S2[row][col];
}

void Aes::deShiftRows(int arr[4][4]){
    int *p2 = arr[1];
    int *p3 = arr[2];
    int *p4 = arr[3];

    leftLoop4int(p2, 3);
    leftLoop4int(p3, 2);
    leftLoop4int(p4, 1);
}

void Aes::deMixColumns(int arr[4][4]){
    int tempArray[4][4];

	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			tempArray[i][j] = arr[i][j];

	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++){
			arr[i][j] = GFMul(deColM[i][0],tempArray[0][j]) ^ GFMul(deColM[i][1],tempArray[1][j]) 
				^ GFMul(deColM[i][2],tempArray[2][j]) ^ GFMul(deColM[i][3], tempArray[3][j]);
		}
}

void Aes::getArrayFrom4W(int i, int array[4][4]){
    int index = i * 4;
	int colOne[4], colTwo[4], colThree[4], colFour[4];
	splitIntToArray(w[index], colOne);
	splitIntToArray(w[index + 1], colTwo);
	splitIntToArray(w[index + 2], colThree);
	splitIntToArray(w[index + 3], colFour);

	for(int i = 0; i < 4; i++) {
		array[i][0] = colOne[i];
		array[i][1] = colTwo[i];
		array[i][2] = colThree[i];
		array[i][3] = colFour[i];
	}
}

void Aes::addRoundTowArray(int aArray[4][4],int bArray[4][4]) {
	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 4; j++)
			aArray[i][j] = aArray[i][j] ^ bArray[i][j];
}