#include <iostream> 
using namespace std;

void OBST1(double a[], double b[], int n, double** m, int** s, double** w)//s[i][j]������������T(i,j)�ĸ��ڵ���Ԫ��
{
	//��ʼ���������ڲ��ڵ�����
	for (int i = 0; i <= n; i++)
	{
		w[i + 1][i] = a[i];
		m[i + 1][i] = 0;
	}

	for (int r = 0; r < n; r++)//r������ֹ�±�Ĳ�
	{
		for (int i = 1; i <= n - r; i++)//iΪ��ʼԪ���±�
		{
			int j = i + r;//jΪ��ֹԪ���±�

			//����T[i][j]����дw[i][j],m[i][j],s[i][j]
			//��ѡi��Ϊ������������Ϊ�գ�������Ϊ�ڵ�
			w[i][j] = w[i][j - 1] + a[j] + b[j];
			m[i][j] = m[i + 1][j];
			s[i][j] = i;

			//��ѡi��Ϊ������kΪ�������k=i+1������j
			//������Ϊ�ڵ㣺i,i+1����k-1,������Ϊ�ڵ㣺k+1,k+2,����j
			for (int k = i + 1; k <= j; k++)
			{
				double t = m[i][k - 1] + m[k + 1][j];

				if (t < m[i][j])
				{
					m[i][j] = t;
					s[i][j] = k;//���ڵ�Ԫ��
				}
			}
			m[i][j] += w[i][j];
		}
	}
}

void OBST2(double a[], double b[], int n, double** m, int** s, double** w)
{
	//��ʼ���������ڲ��ڵ�����
	for (int i = 0; i <= n; i++)
	{
		w[i + 1][i] = a[i];
		m[i + 1][i] = 0;
		s[i + 1][i] = 0;
	}

	for (int r = 0; r < n; r++)//r������ֹ�±�Ĳ�
	{
		for (int i = 1; i <= n - r; i++)//iΪ��ʼԪ���±�
		{
			int j = i + r;//jΪ��ֹԪ���±�
			int i1 = s[i][j - 1] > i ? s[i][j - 1] : i;
			int j1 = s[i + 1][j] > i ? s[i + 1][j] : j;

			//����T[i][j]����дw[i][j],m[i][j],s[i][j]
			//��ѡi��Ϊ������������Ϊ�գ�������Ϊ�ڵ�
			w[i][j] = w[i][j - 1] + a[j] + b[j];
			m[i][j] = m[i][i1 - 1] + m[i1 + 1][j];
			s[i][j] = i1;

			//��ѡi��Ϊ������kΪ�������k=i+1������j
			//������Ϊ�ڵ㣺i,i+1����k-1,������Ϊ�ڵ㣺k+1,k+2,����j
			for (int k = i1 + 1; k <= j1; k++)
			{
				double t = m[i][k - 1] + m[k + 1][j];

				if (t <= m[i][j])
				{
					m[i][j] = t;
					s[i][j] = k;//���ڵ�Ԫ��
				}
			}
			m[i][j] += w[i][j];
		}
	}
}

void traceback(int n, int i, int j, int** s, int f, char ch)//����������Ŷ���������
{
	int k = s[i][j];
	if (k > 0)
	{
		if (f == 0)
		{
			//��
			cout << "���ڵ㣺" << k << " (i:j):(" << i << "," << j << ")" << endl;
		}
		else
		{
			//����
			if (ch=='L')
			{
				cout << f <<"��������Ϊ:"<< k << " (i:j):(" << i << "," << j << ")" << endl;
			}
			else if (ch == 'R')
			{
				cout << f << "��������Ϊ:" << k << " (i:j):(" << i << "," << j << ")" << endl;
			}
		}

		int t = k - 1;
		if (t >= i && t <= n)
		{
			//����������
			traceback(n, i, t, s, k, 'L');
		}
		t = k + 1;
		if (t <= j)
		{
			//����������
			traceback(n, t, j, s, k, 'R');
		}
	}
}

int main()
{
	int N;
	cout << "������N(����������Ԫ�ظ���)��";
	cin >> N;
	double* a = new double[N + 1];
	double* b = new double[N + 1];
	cout << "���������򼯲��ҳɹ��ĸ��ʷֲ�(�����Կո�ָ�)��";
	b[0] = 0.00;
	for (int i = 1; i < N+1; i++)
	{
		cin >> b[i];
	}
	cout << "���������򼯲���ʧ�ܵĸ��ʷֲ�(�����Կո�ָ�)��";
	for (int i = 0; i < N + 1; i++)
	{
		cin >> a[i];
	}
	cout << "���򼯵ĸ��ʷֲ�Ϊ��" << endl;
	cout << "���ҳɹ���" << endl;
	for (int i = 1; i < N+1; i++)
	{
		cout << "b" << i << "=" << b[i] << endl;
	}
	cout << "����ʧ�ܣ�" << endl;
	for (int i = 0; i < N + 1; i++)
	{
		cout << "a" << i << "=" << a[i] << endl;
	}
	double** m = new double* [N + 2];
	int** s = new int* [N + 2];
	double** w = new double* [N + 2];

	for (int i = 0;i < N + 2;i++)
	{
		m[i] = new double[N + 2];
		s[i] = new int[N + 2];
		w[i] = new double[N + 2];
	}

	OBST1(a, b, N, m, s, w);
	cout << "O(n^3)�㷨��" << endl;
	cout << "������������Сƽ��·��Ϊ��" << m[1][N] << endl;
	cout << "��������Ŷ�����Ϊ:" << endl;
	traceback(N, 1, N, s, 0, '0');
	OBST2(a, b, N, m, s, w);
	cout << "O(n^2)�㷨��" << endl;
	cout << "������������Сƽ��·��Ϊ��" << m[1][N] << endl;
	cout << "��������Ŷ�����Ϊ:" << endl;
	traceback(N, 1, N, s, 0, '0');

	for (int i = 0;i < N + 2;i++)
	{
		delete m[i];
		delete s[i];
		delete w[i];
	}
	delete[] m;
	delete[] s;
	delete[] w;
	system("pause");
	return 0;
}