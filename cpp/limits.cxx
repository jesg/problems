

#include <iostream>
#include <climits>

int main()
{

	using namespace std;
	int n_int = 0;
	long n_long = 0;
	long long n_long_long = 0;

	cout << "int " << sizeof n_int << " bytes" << endl;
	cout << "long " << sizeof n_long << " bytes" << endl;
	cout << "long long " << sizeof n_long_long << " bytes" << endl;
	cout << "bits in byte " << CHAR_BIT << endl;
	return 0;
}
