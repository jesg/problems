
#include <iostream>
int times_five(int);

int main()
{
	using namespace std;

	int count;

	cout << "Hello World!";
	cout << endl;
	cin >> count;
	cout << times_five(count) << endl;
	return 0;
}

int times_five(int val)
{
	return val * 5;
}
