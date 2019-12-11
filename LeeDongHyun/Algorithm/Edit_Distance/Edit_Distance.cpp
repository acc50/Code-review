#include <iostream>


int min(int a, int b)
{
	/*std::cout << "a " << a << " b " << b << std::endl;*/
	if (a < b)
		return a;
	else
		return b;
}

int edit_distance(int m, int n, char str1[], char str2[])
{
	int **arr = new int*[m + 1];

	for (int i = 0; i < m + 1; ++i)
		arr[i] = new int[n + 1];				// m+1 행 n+1 열 배열 생성



	for (int i = 0; i < m + 1; ++i)			// 배열의 초기화
		arr[i][0] = i;

	for (int j = 0; j < n + 1; ++j)
		arr[0][j] = j;


	int k = 0;

	for (int i = 1; i < m + 1; ++i) {
		for (int j = 1; j < n + 1; ++j) {


			if (str1[i - 1] == str2[j - 1]) 		// si != ti
				k = 0;
			else
				k = 1;

			arr[i][j] = min(arr[i][j - 1] + 1, min(arr[i - 1][j] + 1, arr[i - 1][j - 1] + k));

		}
	}


	for (int i = 0; i < m + 1; ++i) {
		for (int j = 0; j < n + 1; ++j) {
			std::cout << arr[i][j] << " ";
		}
		std::cout << std::endl;
	}
	std::cout << std::endl;

	int result = arr[m][n];

	for (int i = 0; i < m; ++i)
		delete [] arr[i];
	delete[] arr;

	return result;
}

int main()
{
	char str1[] = { "strong" };
	char str2[] = { "stone" };

	int m = strlen(str1);
	int n = strlen(str2);

	std::cout << "편집거리 : " << edit_distance(m, n, str1, str2) << std::endl;

}