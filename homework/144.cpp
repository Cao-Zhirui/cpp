#include <iostream>
using namespace std;

// 全局变量
int map[9][9];
int path[81][2];
int step = 0;
bool found = false;

// 方向数组：上、右、下、左
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

// DFS函数
bool DFS(int x, int y) {
    // 将当前点加入路径
    path[step][0] = x;
    path[step][1] = y;
    step++;
    
    // 标记当前点为已访问
    map[x][y] = 0;
    
    // 检查是否到达出口（最外圈）
    if (x == 0 || x == 8 || y == 0 || y == 8) {
        return true;
    }
    
    // 尝试四个方向
    for (int i = 0; i < 4; i++) {
        int nx = x + dx[i];
        int ny = y + dy[i];
        
        // 检查新位置是否合法且可通行
        if (nx >= 0 && nx < 9 && ny >= 0 && ny < 9 && map[nx][ny] == 1) {
            if (DFS(nx, ny)) {
                return true;
            }
        }
    }
    
    // 如果四个方向都走不通，回溯
    step--;
    return false;
}

int main() {
    // 读取地图
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cin >> map[i][j];
        }
    }
    
    // 读取起始坐标
    int a, b;
    cin >> a >> b;
    
    // 执行DFS搜索
    DFS(a, b);
    
    // 输出路径
    for (int i = 0; i < step; i++) {
        cout << path[i][0] << "," << path[i][1] << endl;
    }
    
    return 0;
}