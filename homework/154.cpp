#include <iostream>
#define ARRAY_LENGTH 50
using namespace std;

void decode(char* p){
    int n = 0;
    while(p[n] != '\0') n += 1;
    
    char res[ARRAY_LENGTH] = {};
    int left = 0, right = n - 1;
    int index = 0;
    
    // 左右交替取字符
    while (left <= right) {
        if (left <= right) {
            res[index++] = p[left++];  
        }
        if (left <= right) {
            res[index++] = p[right--];  
        }
    }
    
    for(int i = 0; i < n; i++){
        cout << res[i];
    }
}

int main()
{
    char str[ARRAY_LENGTH] = {};
    cin.getline(str, ARRAY_LENGTH);

    decode(str);

    return 0;
}