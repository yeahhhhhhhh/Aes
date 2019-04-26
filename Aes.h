#ifndef __AES__
#define __AES__

class Aes{
  public:
    Aes();
    ~Aes();
    
    // 加密
    void encrypt(char *p, int len, char *key);  
    // 解密 
    void decrypt(char *p, int len, char *key); 

  private:
    // 密钥扩展
    void extendKey(char *key);
    // 轮密钥加
    void addRoundKey(int arr[4][4], int round);
    void addRoundTowArray(int aArray[4][4],int bArray[4][4]);
    // 字节代换
    void subBytes(int arr[4][4]);
    // 行位移
    void shiftRows(int arr[4][4]);
    // 一行位移
    void leftLoop4int(int arr[4], int step);
    // 列混合
    void mixColumns(int arr[4][4]);
    // 逆行位移
    void deShiftRows(int arr[4][4]);
    // 逆列混合
    void deMixColumns(int arr[4][4]); 
    // 逆字节代换
    void deSubBytes(int arr[4][4]);
    // T函数
    int T(int w, int j);

    int getWordFromStr(char *key);
    int getIntFromChar(char key);
    void getArrayFrom4W(int i, int array[4][4]);
    int getNumFromSBox(int num);
    int getNumFromS1Box(int num);
    void splitIntToArray(int w, int arr[4]);
    int mergeArrayToInt(int arr[4]);
    void convertToIntArray(char *p, int arr[4][4]);
    void convertArrayToStr(int arr[4][4], char *p);
    int GFMul(int n, int s);
    int GFMul2(int s);
    int GFMul3(int s);
    int GFMul4(int s);
    int GFMul8(int s);
    int GFMul9(int s);
    int GFMul11(int s);
    int GFMul12(int s);
    int GFMul13(int s);
    int GFMul14(int s);
    
  private:
    // 常量轮值表
    static const int rcon[10];
    // S盒
    static const int S[16][16];
    // 逆S盒
    static const int S2[16][16];
    // 列混合要用到的矩阵
    static const int colM[4][4];
    // 逆列混合用到的矩阵
    static const int deColM[4][4];
    // 密钥扩展后的数组
    int w[44]; // key extends arr
};

#endif // __AES__