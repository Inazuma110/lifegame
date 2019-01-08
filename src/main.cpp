#include <iostream>
#include <unistd.h>
#include <vector>

int n = 10;

void view(std::vector<std::vector<int>> v)
{
  for (int i = 1; i < n+1; i++)
  {
    for (int j = 1; j < n+1; j++)
    {
      if (v[i][j] == 0)
        std::cout << "□ ";
      else if (v[i][j] == 1)
        std::cout << "■ ";
    }
    std::cout << std::endl;
  }
  std::cout << std::endl;
}

using std::cout;
using std::endl;
// セルの数を数え上げる
int counter(std::vector<std::vector<int>> v, int y, int x)
{
  int count = 0;
  int dx[] = {1, 1, 1, 0, 0, -1, -1, -1};
  int dy[] = {1, 0, -1, 1, -1, 1, 0, -1};
  for (int i = 0; i < 8; i++) {
    if(v[y+dy[i]][x+dx[i]] == 1) count++;
    // cout << y+dy[i] << " : " << x+dx[i] << " : " << v[y+dy[i]][x+dx[i]] << endl;
  }
  // cout << x << " : " << y << " : " << count << endl;
  // cout << count << endl;
  // cout << "=======" << endl;
  return count;
}

// 生死判定を行う
int live_check(std::vector<std::vector<int>> v, int y, int x)
{
  int count = counter(v, y, x);
  // cout << count << endl;
  if(v[y][x] == 0){
    if(count == 3) return 1;
    else return 0;
  }else{
    if(count == 2 || count == 3) return 1;
    else return 0;
  }
}

// mapを書きかえる
std::vector<std::vector<int>> reload_map(std::vector<std::vector<int>> v)
{
  using std::vector;
  vector<vector<int>> tmp(12, vector<int>(12, 0));
  for (int i = 1; i < n+1; i++) {
    for (int j = 1; j < n+1; j++) {
      tmp[i][j] = live_check(v, i, j);
      // cout << live_check(v, i, j) << endl;
    }
  }
  for (int i = 0; i < n+1; i++) {
    for (int j = 0; j < n+1; j++) {
      v[j][i] = tmp[j][i];
    }
  }

  return v;
}

int main()
{
  std::vector<std::vector<int>> cell(12, std::vector<int>(12,0));

  cell[1][2] = 1;
  cell[2][3] = 1;
  cell[3][1] = 1;
  cell[3][2] = 1;
  cell[3][3] = 1;

  view(cell);

  int w = 0;
  while(w++ < 100)
  {
    view(cell);
    cell = reload_map(cell);
    sleep(1);
  }
}
