
#include <iostream>

struct name {
	const char first_name[200];
	const char last_name[200];
};

int main()
{
	using namespace std;

	name naru = {"naru", "kotoishi"};

	cout << naru.first_name << " " << naru.last_name << endl;
	return 0;
}
