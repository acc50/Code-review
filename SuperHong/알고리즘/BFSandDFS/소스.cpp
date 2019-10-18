#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#define N 6
bool vist[N] = { false, };
std::stack<int> stack;
std::queue<int> queue;
int G[N][N] =
{
	{0,1,1,1,0,1},
	{1,0,1,0,0,0},
	{1,1,0,0,1,0},
	{1,0,0,0,0,1},
	{0,0,1,0,0,1},
	{1,0,0,1,1,0}
};
void DFS(int num);
void BFS(int num);
int main()
{
	std::cout << "시작노드 입력:"; int num = 0; std::cin >> num;
	std::cout << '\n';

	std::cout << "DFS\n";
	DFS(num);
	for (int i = 0; i < N; i++)vist[i] = false;
	std::cout << "BFS\n";
	BFS(num);

}

void DFS(int num)
{
	vist[num] = true;
	std::cout << "시작노드: " << num << '\n';
	for (int i = 0; i < N; i++) {
		if (vist[i] == false) {
			if (G[num][i] == 1) {
				DFS(i);
				return;
			}
		}
	}
	

}
void BFS(int num)
{

	vist[num] = true;
	std::cout << "시작노드: " << num << '\n';
	for (int i = 0; i < N; i++) {
		if (!vist[i])
		{
			if (G[num][i] == 1) {
				queue.push(i);
				vist[i] = true;
			}
		}
	}
	queue;
	
	while (!queue.empty()) {
		int newnum = queue.front();
		queue.pop();
		BFS(newnum);
	}


}