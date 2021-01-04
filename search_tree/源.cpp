#include <iostream> 
using namespace std;

void OBST1(double a[], double b[], int n, double** m, int** s, double** w)//s[i][j]保存最优子树T(i,j)的根节点中元素
{
	//初始化构造无内部节点的情况
	for (int i = 0; i <= n; i++)
	{
		w[i + 1][i] = a[i];
		m[i + 1][i] = 0;
	}

	for (int r = 0; r < n; r++)//r代表起止下标的差
	{
		for (int i = 1; i <= n - r; i++)//i为起始元素下标
		{
			int j = i + r;//j为终止元素下标

			//构造T[i][j]，填写w[i][j],m[i][j],s[i][j]
			//首选i作为根，其左子树为空，右子树为节点
			w[i][j] = w[i][j - 1] + a[j] + b[j];
			m[i][j] = m[i + 1][j];
			s[i][j] = i;

			//不选i作为根，设k为其根，则k=i+1，……j
			//左子树为节点：i,i+1……k-1,右子树为节点：k+1,k+2,……j
			for (int k = i + 1; k <= j; k++)
			{
				double t = m[i][k - 1] + m[k + 1][j];

				if (t < m[i][j])
				{
					m[i][j] = t;
					s[i][j] = k;//根节点元素
				}
			}
			m[i][j] += w[i][j];
		}
	}
}

void OBST2(double a[], double b[], int n, double** m, int** s, double** w)
{
	//初始化构造无内部节点的情况
	for (int i = 0; i <= n; i++)
	{
		w[i + 1][i] = a[i];
		m[i + 1][i] = 0;
		s[i + 1][i] = 0;
	}

	for (int r = 0; r < n; r++)//r代表起止下标的差
	{
		for (int i = 1; i <= n - r; i++)//i为起始元素下标
		{
			int j = i + r;//j为终止元素下标
			int i1 = s[i][j - 1] > i ? s[i][j - 1] : i;
			int j1 = s[i + 1][j] > i ? s[i + 1][j] : j;

			//构造T[i][j]，填写w[i][j],m[i][j],s[i][j]
			//首选i作为根，其左子树为空，右子树为节点
			w[i][j] = w[i][j - 1] + a[j] + b[j];
			m[i][j] = m[i][i1 - 1] + m[i1 + 1][j];
			s[i][j] = i1;

			//不选i作为根，设k为其根，则k=i+1，……j
			//左子树为节点：i,i+1……k-1,右子树为节点：k+1,k+2,……j
			for (int k = i1 + 1; k <= j1; k++)
			{
				double t = m[i][k - 1] + m[k + 1][j];

				if (t <= m[i][j])
				{
					m[i][j] = t;
					s[i][j] = k;//根节点元素
				}
			}
			m[i][j] += w[i][j];
		}
	}
}

void traceback(int n, int i, int j, int** s, int f, char ch)//回溯输出最优二叉搜索树
{
	int k = s[i][j];
	if (k > 0)
	{
		if (f == 0)
		{
			//根
			cout << "根节点：" << k << " (i:j):(" << i << "," << j << ")" << endl;
		}
		else
		{
			//子树
			if (ch=='L')
			{
				cout << f <<"的左子树为:"<< k << " (i:j):(" << i << "," << j << ")" << endl;
			}
			else if (ch == 'R')
			{
				cout << f << "的右子树为:" << k << " (i:j):(" << i << "," << j << ")" << endl;
			}
		}

		int t = k - 1;
		if (t >= i && t <= n)
		{
			//回溯左子树
			traceback(n, i, t, s, k, 'L');
		}
		t = k + 1;
		if (t <= j)
		{
			//回溯右子树
			traceback(n, t, j, s, k, 'R');
		}
	}
}

int main()
{
	int N;
	cout << "请输入N(代表有序集中元素个数)：";
	cin >> N;
	double* a = new double[N + 1];
	double* b = new double[N + 1];
	cout << "请输入有序集查找成功的概率分布(概率以空格分隔)：";
	b[0] = 0.00;
	for (int i = 1; i < N+1; i++)
	{
		cin >> b[i];
	}
	cout << "请输入有序集查找失败的概率分布(概率以空格分隔)：";
	for (int i = 0; i < N + 1; i++)
	{
		cin >> a[i];
	}
	cout << "有序集的概率分布为：" << endl;
	cout << "查找成功：" << endl;
	for (int i = 1; i < N+1; i++)
	{
		cout << "b" << i << "=" << b[i] << endl;
	}
	cout << "查找失败：" << endl;
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
	cout << "O(n^3)算法：" << endl;
	cout << "二叉搜索树最小平均路长为：" << m[1][N] << endl;
	cout << "构造的最优二叉树为:" << endl;
	traceback(N, 1, N, s, 0, '0');
	OBST2(a, b, N, m, s, w);
	cout << "O(n^2)算法：" << endl;
	cout << "二叉搜索树最小平均路长为：" << m[1][N] << endl;
	cout << "构造的最优二叉树为:" << endl;
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