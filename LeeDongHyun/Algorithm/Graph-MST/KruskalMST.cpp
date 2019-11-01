#include <iostream>

using namespace std;
constexpr auto N = 6;
int cnt = 0;
int w = 0;

typedef struct List{
	int p1, p2;
	int weigh;
	struct List *next;
}list;

void Reset_Graph(int G[][N])
{
	for (int i = 0; i < N; ++i) {
		for (int j = 0; j < N; ++j) {
			G[i][j] = 0;
		}
	}
}

void Make_Set(int p[])
{
	for (int i = 0; i < N; ++i)
		p[i] = i;
}

int Find_Set(int x, int p[])
{
	if (x == p[x])			// x가 x의 부모이면 리턴
		return x;
	else
		return Find_Set(p[x], p);		// 아니면 재귀
}

void Union(int x, int y, int p[], list *k)
{
	if (p[Find_Set(x, p)] != p[Find_Set(y, p)]) {		// x의부모!= y의부모
		p[Find_Set(y, p)] = Find_Set(x, p);		// y의 부모 = x의 부모

		cout << "간선 " << ++cnt << "(" << x << ", " << y << ")" <<		// 병합 할 시 간선 출력
			"가중치 " << k->weigh << endl;
		w = w + k->weigh;
	}
}

void KruskalMST(int G[][N], int p[], list *head)
{
	Reset_Graph(G);		// 트리의 초기화
	
	Make_Set(p);		// 셋 만들기


	for (list *k = head; k->next != nullptr;) {		// 리스트를 탐색
		
		Union(k->p1, k->p2, p, k);		// 병합 함수

		list *temp = k;		// 삭제용 임시 list 포인터
		k = k->next;		// k를 다음으로 옮김
		delete temp;		// temp 삭제
	}

	cout << "가중치의 합 " << w << endl;
}

int main()
{
	int G[N][N] = {
		{0,8,2,0,4,0},
		{8,0,4,1,0,2},
		{2,4,0,0,3,7},
		{0,1,0,0,0,1},
		{4,0,3,0,0,9},
		{0,2,7,1,9,0} };

	list *head = nullptr;
	bool check = false;

	for (int i = 0; i < 6; ++i) {			// 리스트의 생성
		for (int j = 0; j < 6; ++j) {

			if (G[i][j] != 0) {

				if (head != nullptr) {
					for (list *p = head; p->next != nullptr; p = p->next) {
						if ((i == p->p1 && j == p->p2) ||
							(j == p->p1 && i == p->p2))
						{
							check = true;
						}
					}
				}

				if (check == false || head == nullptr) {		// 중복이 아닐경우
					list *L = new list;
					L->next = nullptr;
					L->p1 = i;
					L->p2 = j;
					L->weigh = G[i][j];

					if (head == nullptr)		// 헤드가 비어있으면 대입
						head = L;

					else {							// 비어있지않으면
						list *temp = head;		// temp = head
						while (temp->next != nullptr)		// 리스트의 끝까지 감
							temp = temp->next;
						temp->next = L;		// 리스트 끝의 next 는 L
					}
				}

			}
			check = false;
		}
	}

	for (list *p = head; p->next != nullptr; p = p->next) {				// 리스트의 오름차순 정렬
		for (list *k = p->next; k->next != nullptr; k = k->next) {

			if (p->weigh > k->weigh) {
				int temp = p->weigh;
				p->weigh = k->weigh;
				k->weigh = temp;

				temp = p->p1;
				p->p1 = k->p1;
				k->p1 = temp;

				temp = p->p2;
				p->p2 = k->p2;
				k->p2 = temp;

			}

		}
	}

	for (list *p = head; p->next != nullptr; p = p->next)								// 리스트 확인용
		cout << p->p1 + 1 << " " << p->p2 + 1 << " " << p->weigh << " " << endl;

	int parent[N] = { 0, };
	KruskalMST(G, parent, head);

}