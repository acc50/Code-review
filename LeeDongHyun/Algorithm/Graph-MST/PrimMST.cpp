#include <iostream>

using namespace std;
constexpr auto N = 6;

typedef struct List {
	int p1, p2;
	int weight;
}list;

list D[N];
list T[N];
int cnt = 0;

void reset(int G[][N])
{
	for (int i = 0; i < N; ++i)
		for (int j = 0; j < N; ++j)
			G[i][j] = 0;
}

void PrimMST(int G[][N])
{
	int start = 3;		// 시작점 vertex 3

	for (int i = 0; i < N; ++i) {
		if (G[start][i] != 0 && i != start) {	// 3번과 연결된 것
			D[i].weight = G[start][i];		// 가중치를 D 에 넣고
			D[i].p1 = start;				// p1, p2 를 3번, 연결된 점 으로 함
			D[i].p2 = i;
		}
		else {
			D[i].weight = 10000;		// 연결x 인 곳은 가중치에 최댓값
		}
	}
	T[cnt].p1 = start;	// 초기 트리T는 시작점을 가짐
	D[start].weight = 0;

	int min = 10000;		// 최소 가중치
	int min_number = 0;

	while (cnt < N - 1) {		// MST의 경우 간선은 (Vertex의 수 - 1) 개

		for (int i = 0; i < N; ++i) {		// 가중치 탐색
			if (D[i].weight != 0 && D[i].weight < min) {	// 가중치가 0이 아니고, 최소가중치보다 작으면
				min = D[i].weight;							// D 리스트에 있는 가중치의 최솟값을 min 에 넣음
				min_number = i;								// 최솟값에 해당하는 vertex를 가져옴
			}
		}
		T[cnt].p1 = D[min_number].p1;	// D[].p1 엔 간선 중 가장 가중치가 작은 시작점의 번호가 있음
		T[cnt].p2 = min_number;			// 연결된 점을 p2 에 넣음
		T[cnt].weight = min;			// 최소 가중치를 넣음
		D[min_number].weight = 0;		// T에 있는 값의 가중치는 0으로 만듬		 가중치가 0일경우 T에 속해있는것으로 판단해 탐색에서 제외
		min = 10000;					// 가중치 최솟값 초기화


		for (int i = 0; i < N; ++i) {		// 가중치 갱신
			
			if (G[min_number][i] != 0 && D[i].weight != 0 && G[min_number][i] < D[i].weight) {	// 새로운 점과 연결된점 && T에 속하지 않은점 && D의 가중치보다 작을경우
				D[i].weight = G[min_number][i];		// 가중치값 넣음
				D[i].p1 = min_number;				// 새로운값과 연결된 것을 탐색하는 것이므로 새로운 값을 p1에 저장
				D[i].p2 = i;						// 연결된 것중 가중치가 작은 것들 p2에 저장
			}
		}
		++cnt;

	}

	reset(G);

	for (int i = 0; i < cnt; ++i) {
		G[T[i].p1][T[i].p2] = T[i].weight;
		G[T[i].p2][T[i].p1] = T[i].weight;
		cout << "간선" << i + 1 << ": (" << T[i].p1 << ", " << T[i].p2 << ") 의 가중치   " << T[i].weight << endl;
	}
}


int main()
{
	int G[N][N] = {
		{0,3,2,0,4,0},
		{3,0,4,1,0,2},
		{2,4,0,0,5,7},
		{0,1,0,0,0,1},
		{4,0,5,0,0,9},
		{0,2,7,1,9,0} };
	
	PrimMST(G);

	cout << endl << "PrimMST 결과 " << endl;
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			cout << G[i][j] << " ";
		}
		cout << endl;
	}
			
}