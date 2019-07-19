#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>

using namespace std;

const int maxLifeguard = 100010;

struct lifeguard
{
	int h,t;
} a[maxLifeguard];

void qsort(int h, int t)
{
	int i = h, j = t;
	lifeguard x = a[h];
	while (i < j)
	{
		while (((a[j].h > x.h)||((a[j].h == x.h)&&(a[j].t < x.t)))&&(i < j)) j--;
		if (i < j)
		{
			a[i] = a[j];
			i++;
		}
		while (((a[i].h < x.h)||((a[i].h == x.h)&&(a[i].t > x.t)))&&(i < j)) i++;
		if (i < j)
		{
			a[j] = a[i];
			j--;
		}
	}
	a[i] = x;
	if (h < j)
		qsort(h, j - 1);
	if (i < t)
		qsort(i + 1, t);

}

int main()
{
	//freopen("10.in","r",stdin);
	//freopen("10.out","w",stdout);
	
	int i;
	int num = 0;
	bool lap = false;
	
	cin >> num;
	for (i = 1; i <= num; i++)
		cin >> a[i].h >> a[i].t;
	
	qsort(1, num);
	//for (i = 1; i <= num; i++)
	//	cout << a[i].h << a[i].t << endl;

	a[0].h = a[1].h - 1; a[0].t = a[0].h;
	a[num + 1].h = a[num].t + 1; a[num + 1].t = a[num + 1].h;

	for (i = 2; i <= num; i++)
		if (a[i].t <= a[i - 1].t)
			lap = true;


	int ans = 0;
	int maxRightPosition = a[0].t;
	for (i = 1; i <= num; i++)
		if (a[i].h >= maxRightPosition)
		{
			ans += (a[i].t - a[i].h);
			maxRightPosition = a[i].t;
		}
		else if (a[i].t > maxRightPosition)
		{
			ans += (a[i].t - maxRightPosition);
			maxRightPosition = a[i].t;
		}
	if (lap)
		cout << ans << endl;
	else
	{
		int minCost = ans;
		for (i = 1; i <= num; i++)
		{
			if (a[i - 1].t >= a[i + 1].h)
			{
				minCost = 0;
				break;
			}
			else
			{
				int temp = min(a[i].t, a[i + 1].h) - max(a[i].h, a[i - 1].t);
				if (temp < minCost)
					minCost = temp;
			}
		}
		cout << ans - minCost << endl;
	}

	return 0;
}