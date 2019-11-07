#include <iostream>	
#include <vector>
const int V = 6;
void PRIMMST(int G[][V], int start);
int D[V] = { 0, };
int min(int* D);
int main()
{
	int G[][V] = {
	{0,3,2,0,4,0},
	{3,0,4,1,0,2},
	{2,4,0,0,5,7},
	{0,1,0,0,0,1},
	{4,0,5,0,0,9},
	{0,2,7,1,9,0}
	};
	PRIMMST(G, 3);
}
void PRIMMST(int G[][V], int start)
{
	D[start] = 0;//배열 D는 가중치를 담아놓는다. 최초시작점은 당연히 0이다 (본인위치에서 본인위치로의 가중치는 당연히 0)
	for (int i = 0; i < V; i++) {
		if (G[start][i] != 0) { //최초시작점하고 연결되어있는 점들의 가중치를 D에 넣는다.
			D[i] = G[start][i];
		}
		else
			D[i] = 999; //연결안되었다면 엄청높은값(무한)을 넣어준다.
	}
	bool empty[V] = { false, };//중복을 피하기위해서 넣었다. 만약 최소신장트리점이 추가되면 그점을 true그렇지 않으면 false이다.
	std::vector<int> v;
	v.push_back(start); //최초값을 최소신장트리 점들의 집합V에 넣어준다.
	empty[start] = true; //넣어준값을 true처리를 해준다.
	while (v.size() < V) {
		int minNum = min(D);//현재 연결할수있는 점에서 가중치가 가작작은 점

		for (int i = 0; i < v.size(); ++i) {
			if (!empty[minNum]) { //중복을 피하고 무한루프에 빠지는것을 막는다.
				if (G[minNum][v[i]] == D[minNum]) { //현재 연결할수있는 점에서 가중치가 가작작은 점과 최소신장트리에 있는점을 찾는다.
					v.push_back(minNum); //현재 연결할수있는 점에서 가중치가 가작작은 점을 최소신장트리 점들의 집합V에 넣어준다.
					empty[minNum] = true; //그값을 true로 바꿔준다.

					std::cout << v[i] << ',' << minNum << "의 가중치:" << G[v[i]][minNum] << '\n';
					D[minNum] = 999; //넣었으면 D추가한점과 원래있던점 v[i]간의 거리를 999로 초기화를 해주었다.
				}
			}
			else
				break; // 이미있으면 검사할 필요도 없이 반복문을 나간다.
		}
		for (int i = 0; i < V; i++) {
			if (!empty[i]) {
				if (G[minNum][i] <D[i]&&G[minNum][i]!=0)//minNum점과 연결될수 있는점i에서 가중치가 D[i]보다 작고(그점에대한 최소 가중치를 넣기위해)  G[minNum][i]!=0    
					D[i] = G[minNum][i];				// 이 아니면(0이면 자기자신이니깐) D[i]에 G[minNum][i]을 넣어준다.(새로운 가중치를 넣기)
			}
		}
	}
}
int min(int* D)
{
	int min = 9993;
	int num = 0;
	for (int i = 0; i < V; i++)
	{
		if (min > D[i]&&D[i]!=0) {
			min = D[i];
			num = i;
		}
	}
	return num;
}