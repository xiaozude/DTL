#include <stack>

void InsertSort(int A[], int n)
{
	for (int i = 2, j; i <= n; i++)
	{
		A[0] = A[i];
		for (j = i; A[j - 1] > A[0]; j--)
		{
			A[j] = A[j - 1];
		}
		A[j] = A[0];
	}
}

void SelectSort(int A[], int n)
{
	for (int i = 1; i < n; i++)
	{
		int min = i;
		for (int j = i; j <= n; j++)
		{
			if (A[j] < A[min])
			{
				min = j;
			}
		}
		A[0] = A[i];
		A[i] = A[min];
		A[min] = A[0];
	}
}

void BubbleSort(int A[], int n)
{
	bool flag = true;
	for (int i = n; i > 1 && flag; i--)
	{
		flag = false;
		for (int j = 1; j < i; j++)
		{
			if (A[j] > A[j + 1])
			{
				flag = true;
				A[0] = A[j];
				A[j] = A[j + 1];
				A[j + 1] = A[0];
			}
		}
	}
}

void QuickSort(int A[], int low, int high)
{
	if (low >= high) return;
	int left = low;
	int right = high;
	A[0] = A[low];
	while (low < high)
	{
		while (low < high && A[high] >= A[0]) high--;
		A[low] = A[high];
		while (low < high && A[low] <= A[0]) low++;
		A[high] = A[low];
	}
	A[low] = A[0];
	QuickSort(A, left, low - 1);
	QuickSort(A, high + 1, right);
}

void QuickSort(int A[], int n)
{
	std::stack<int> s;
	s.push(n);
	s.push(1);
	while (!s.empty())
	{
		int low = s.top();
		int left = low;
		s.pop();
		int high = s.top();
		int right = high;
		s.pop();
		A[0] = A[low];
		while (low < high)
		{
			while (low < high && A[high] >= A[0]) high--;
			A[low] = A[high];
			while (low < high && A[low] <= A[0]) low++;
			A[high] = A[low];
		}
		A[low] = A[0];
		if (high + 1 < right)
		{
			s.push(right);
			s.push(high + 1);
		}
		if (left < low - 1)
		{
			s.push(low - 1);
			s.push(left);
		}
	}
}

void HeapAdjust(int A[], int low, int high)
{
	A[0] = A[low];
	for (int i = 2 * low; i <= high; i *= 2)
	{
		if (i < high && A[i] < A[i + 1]) i++;
		if (A[0] >= A[i]) break;
		A[low] = A[i];
		low = i;
	}
	A[low] = A[0];
}

void HeapSort(int A[], int n)
{
	if (n <= 1) return;
	for (int i = n / 2; i > 0; i--)
	{
		HeapAdjust(A, i, n);
	}
	for (int i = n; i > 1; i--)
	{
		A[0] = A[i];
		A[i] = A[1];
		A[1] = A[0];
		HeapAdjust(A, 1, i - 1);
	}
}

void Merge(int A[], int B[], int low, int mid, int high)
{
	int i = low;
	int j = mid + 1;
	int k = low;
	while (i <= mid && j <= high)
	{
		if (B[i] < B[j]) A[k++] = B[i++];
		else A[k++] = B[j++];
	}
	while (i <= mid) A[k++] = B[i++];
	while (j <= high) A[k++] = B[j++];
}

void MergeSort(int A[], int low, int high)
{
	if (low >= high) return;
	int mid = (low + high) / 2;
	MergeSort(A, low, mid);
	MergeSort(A, mid + 1, high);
	int * B = new int[high - low + 1];
	for (int i = 1; i <= high - low + 1; i++)
	{
		B[i] = A[i];
	}
	Merge(A, B, low, mid, high);
	delete[] B;
}

void MergePass(int A[], int B[], int s, int n)
{
	int i = 1;
	while (i + 2 * s - 1 <= n)
	{
		Merge(A, B, i, i + s - 1, i + 2 * s - 1);
		i += 2 * s;
	}
	if (i + s - 1 < n)
	{
		Merge(A, B, i, i + s - 1, n);
	}
	else
	{
		for (int j = i; j <= n; j++)
		{
			A[j] = B[j];
		}
	}
}

void MergeSort(int A[], int n)
{
	int * B = new int[n + 1];
	for (int k = 1; k < n; k *= 4)
	{
		MergePass(B, A, k, n);
		MergePass(A, B, k * 2, n);
	}
	delete[] B;
}

