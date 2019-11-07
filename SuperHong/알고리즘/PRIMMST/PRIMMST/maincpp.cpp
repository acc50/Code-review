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
	D[start] = 0;//�迭 D�� ����ġ�� ��Ƴ��´�. ���ʽ������� �翬�� 0�̴� (������ġ���� ������ġ���� ����ġ�� �翬�� 0)
	for (int i = 0; i < V; i++) {
		if (G[start][i] != 0) { //���ʽ������ϰ� ����Ǿ��ִ� ������ ����ġ�� D�� �ִ´�.
			D[i] = G[start][i];
		}
		else
			D[i] = 999; //����ȵǾ��ٸ� ��û������(����)�� �־��ش�.
	}
	bool empty[V] = { false, };//�ߺ��� ���ϱ����ؼ� �־���. ���� �ּҽ���Ʈ������ �߰��Ǹ� ������ true�׷��� ������ false�̴�.
	std::vector<int> v;
	v.push_back(start); //���ʰ��� �ּҽ���Ʈ�� ������ ����V�� �־��ش�.
	empty[start] = true; //�־��ذ��� trueó���� ���ش�.
	while (v.size() < V) {
		int minNum = min(D);//���� �����Ҽ��ִ� ������ ����ġ�� �������� ��

		for (int i = 0; i < v.size(); ++i) {
			if (!empty[minNum]) { //�ߺ��� ���ϰ� ���ѷ����� �����°��� ���´�.
				if (G[minNum][v[i]] == D[minNum]) { //���� �����Ҽ��ִ� ������ ����ġ�� �������� ���� �ּҽ���Ʈ���� �ִ����� ã�´�.
					v.push_back(minNum); //���� �����Ҽ��ִ� ������ ����ġ�� �������� ���� �ּҽ���Ʈ�� ������ ����V�� �־��ش�.
					empty[minNum] = true; //�װ��� true�� �ٲ��ش�.

					std::cout << v[i] << ',' << minNum << "�� ����ġ:" << G[v[i]][minNum] << '\n';
					D[minNum] = 999; //�־����� D�߰������� �����ִ��� v[i]���� �Ÿ��� 999�� �ʱ�ȭ�� ���־���.
				}
			}
			else
				break; // �̹������� �˻��� �ʿ䵵 ���� �ݺ����� ������.
		}
		for (int i = 0; i < V; i++) {
			if (!empty[i]) {
				if (G[minNum][i] <D[i]&&G[minNum][i]!=0)//minNum���� ����ɼ� �ִ���i���� ����ġ�� D[i]���� �۰�(���������� �ּ� ����ġ�� �ֱ�����)  G[minNum][i]!=0    
					D[i] = G[minNum][i];				// �� �ƴϸ�(0�̸� �ڱ��ڽ��̴ϱ�) D[i]�� G[minNum][i]�� �־��ش�.(���ο� ����ġ�� �ֱ�)
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