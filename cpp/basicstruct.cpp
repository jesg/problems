
#include <iostream>
#include <string>

struct name {
	const std::string first_name;
	const std::string last_name;
};

int main()
{
	using namespace std;

	name naru = {"naru", "kotoishi"};

	cout << naru.first_name << " " << naru.last_name << endl;
	return 0;
}
