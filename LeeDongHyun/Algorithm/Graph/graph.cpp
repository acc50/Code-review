#include <iostream>

using namespace std;

constexpr auto N = 6;

void DFS(int G[][N], bool visited[], int n)
{
	if (visited[n] == false) {
		visited[n] = true;
		cout << n + 1 << " ";



		for (int i = 0; i < N; ++i)
			if (G[n][i] == 1)
				DFS(G, visited, i);
	}
}

void enqueue(int queue[], bool visited[], int &back, int n)		// 값을 넣을 때 방문했다 처리함
{
	back = back + 1;
	queue[back] = n + 1;		// n + 1 은 Vertex 가 1부터 있다고 여기기에 n + 1 을 넣음
	visited[n] = true;
}

void dequeue(int queue[], int &front)
{
	front = front + 1;
	cout << queue[front] << " ";
}

void BFS(int G[][N], bool visited[], int Q[], int &back, int &front, int n)
{
	enqueue(Q, visited, back, n);		// 맨 처음 선택한 노드를 큐에 넣음

	while (front < N - 1) {		// 큐는 최대 N개 들어가므로 front 가 N - 1 보다 크면 전부 순회한것
		dequeue(Q, front);

		for (int i = 0; i < 6; i++) {						// 처음 노드에서 인접한 Vertex 들을 찾음
			if (G[n][i] == 1 && visited[i] == false)		
				enqueue(Q, visited, back, i);				// 인접한 Vertex 들을 큐에 넣음
		}
		n = Q[front + 1] - 1;								// 그래프의 다음 순회할 Vertex는 첫번째큐에서 인접한 것중 가장 먼저 들어간 것임
	}
	back = -1;		// 순회 종료시 큐를 다시 사용하기위해 초기값으로 돌려놓음
	front = -1;
}

void Set(bool visited[])		// visited 설정 함수
{
	for (int i = 0; i < N; ++i)
		visited[i] = false;
}

int main()
{

	int G[N][N] =
	{ {0,1,1,1,0,1},
	  {1,0,1,0,0,0},
	  {1,1,0,0,1,0},
	  {1,0,0,0,0,1},
	  {0,0,1,0,0,1},
	  {1,0,0,1,1,0} };

	bool visited[N];

	int Queue[N];
	int back = -1;		// inqueue 시 사용됨
	int front = -1;		// dequeue 시 사용됨


	Set(visited);
	cout << "시작노드 : 1" << endl;
	cout << "DFS: " << endl;
	DFS(G, visited, 0);
	cout << endl << endl;

	cout << "BFS: " << endl;
	Set(visited);
	BFS(G, visited, Queue, back, front, 0);
	cout << endl << endl;


	Set(visited);
	cout << "시작노드 : 2" << endl;
	cout << "DFS: " << endl;
	DFS(G, visited, 1);
	cout << endl << endl;

	cout << "BFS: " << endl;
	Set(visited);
	BFS(G, visited, Queue, back, front, 1);
	cout << endl << endl;


	return 0;

}