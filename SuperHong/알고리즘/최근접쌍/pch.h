// 시작을 위한 팁: 
//   1. [솔루션 탐색기] 창을 사용하여 파일을 추가/관리합니다.
//   2. [팀 탐색기] 창을 사용하여 소스 제어에 연결합니다.
//   3. [출력] 창을 사용하여 빌드 출력 및 기타 메시지를 확인합니다.
//   4. [오류 목록] 창을 사용하여 오류를 봅니다.
//   5. [프로젝트] > [새 항목 추가]로 이동하여 새 코드 파일을 만들거나, [프로젝트] > [기존 항목 추가]로 이동하여 기존 코드 파일을 프로젝트에 추가합니다.
//   6. 나중에 이 프로젝트를 다시 열려면 [파일] > [열기] > [프로젝트]로 이동하고 .sln 파일을 선택합니다.

#ifndef PCH_H
#define PCH_H
#define SIZE 30
struct  myPoint
{
	int x = 0, y = 0;
};
//
extern myPoint minPoint[2];
extern double min;
void mySwap(myPoint&, myPoint&);
void SortByX(myPoint* num, int* copy, int left, int right);//병합정렬 느낌으로 한다
void Merge(myPoint* num,int*copy, int left, int right);
void myQSort(myPoint* num,int left, int right);
void GetMinDis(myPoint* num,int left, int right);//
double GetDis(myPoint, myPoint);
void GetmidDis(myPoint* num, myPoint p);
#endif //PCH_H
