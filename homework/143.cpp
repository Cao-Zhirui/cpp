#include <iostream>
using namespace std;

int step_counter = 1;  

void hanoi(int n, char start, char target, char auxiliary) {
    if (n == 1) {
        cout << step_counter << ". " << start << " -> " << target << endl;
        step_counter++;
    } else {
        // 将n-1个盘子从起始柱移动到辅助柱
        hanoi(n - 1, start, auxiliary, target);
        // 将最大的盘子从起始柱移动到目标柱
        cout << step_counter << ". " << start << " -> " << target << endl;
        step_counter++;
        // 将n-1个盘子从辅助柱移动到目标柱
        hanoi(n - 1, auxiliary, target, start);
    }
}

int main() {
    char start, target;
    int n;
    
    // 读取输入
    cin >> start >> target >> n;
    
    // 确定辅助柱
    char auxiliary;
    if (start != 'A' && target != 'A') {
        auxiliary = 'A';
    } else if (start != 'B' && target != 'B') {
        auxiliary = 'B';
    } else {
        auxiliary = 'C';
    }
   
    hanoi(n, start, target, auxiliary);

    return 0;
}