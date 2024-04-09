#include<iostream>
using namespace std;
void text(int a = 0, int b = 0, int c = 0)
{
	if (a > 1 && b == 0)
		c = c + a;
	if (a == 2 || c > 1)
		c++;
}
int main()
{
	text(3, 1, 1);
	return 0;
}