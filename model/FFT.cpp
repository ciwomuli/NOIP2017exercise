#include <algorithm>
#include <cmath>
#include <cstdio>
#include <iostream>
const double PI = acos(-1);
using namespace std;
struct Virt
{
	double r, i;
	Virt(double a, double b) : r(a), i(b) {}
	Virt()
	{
		Virt(0, 0);
	}
	Virt operator+(const Virt &rch)
	{
		return Virt(r + rch.r, i + rch.i);
	}
	Virt operator-(const Virt &rch)
	{
		return Virt(r - rch.r, i - rch.i);
	}
	Virt operator*(const Virt &rch)
	{
		return Virt(r * rch.r - i * rch.i, r * rch.i + i * rch.r);
	}
};
Virt a[3000100], b[3000100], c[3000100];
void Rader(Virt *F, int len)
{
	int j = len >> 1;
	for (int i = 1; i < len - 1; i++)
	{
		if (i < j)
			swap(F[i], F[j]);
		int k = len >> 1;
		while (j >= k)
		{
			j -= k;
			k >>= 1;
		}
		if (j < k)
			j += k;
	}
}
void DFT(Virt *F, int len, int on)
{
	Rader(F, len);
	for (int h = 2; h <= len; h <<= 1)
	{
		Virt wn(cos(-on * 2 * PI / h), sin(-on * 2 * PI / h));
		for (int j = 0; j < len; j += h)
		{
			Virt w(1, 0);
			for (int k = j; k < j + h / 2; k++)
			{
				Virt u = F[k];
				Virt t = w * F[k + h / 2];
				F[k] = u + t;
				F[k + h / 2] = u - t;
				w = w * wn;
			}
		}
	}
	if (on == -1)
	{
		for (int i = 0; i < len; i++)
		{
			F[i].r /= len;
		}
	}
}
void FFT(Virt *A, Virt *B, Virt *C, int len)
{
	DFT(A, len, 1);
	DFT(B, len, 1);
	for (int i = 0; i < len; i++)
	{
		C[i] = A[i] * B[i];
	}
	DFT(C, len, -1);
}

int main()
{
	int n, m;
	scanf("%d%d", &n, &m);
	for (int i = 0; i <= n; i++)
	{
		scanf("%lf", &a[i].r);
	}
	for (int i = 0; i <= m; i++)
	{
		scanf("%lf", &b[i].r);
	}
	int Lim = 1;
	while (Lim <= n + m)
		Lim <<= 1;
	FFT(a, b, c, Lim);
//	cout << Lim<<endl;
	for (int i = 0; i <= n + m; i++)
		printf("%d ", (int)(c[i].r + 0.5));
}