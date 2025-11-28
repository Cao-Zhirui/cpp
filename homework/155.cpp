//接受一个整型数组，输出数组中每一个字节的十进制值。

#include <iostream>
using namespace std;

int main() {
    int arr[5];
    
    for (int i = 0; i < 5; i++) {
        cin >> arr[i];
    }
    
    for (int i = 0; i < 5; i++) {
        unsigned char* bytes = (unsigned char*)&arr[i];
        for (int j = 0; j < sizeof(int); j++) {
            cout << (int)(signed char)bytes[j];
            if (!(i == 4 && j == 3)) {
                cout << " ";
            }
        }
    }
    
    return 0;
}