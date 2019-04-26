#include <iostream>
#include <stdlib.h>
#include <string.h>

#include "Aes.h"

using namespace std;

int main(int argc, char const *argv[])
{
    char a[49] = "abcdefghijklmnopabcdefghijklmnopabcdefghijklmnop";
    char *p = a;
    cout << "len = " << strlen(a) << endl;

    char key[49] = "abcdefghijklmnopabcdefghijklmnopabcdefghijklmnop";

    Aes aes;
    aes.encrypt(p, 48, key);

    cout << p << endl;

    aes.decrypt(p, 48, key);

    cout << p << endl;

    return 0;
}
