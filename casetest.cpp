#include <iostream>
using namespace std;

int main() {
	string s;
	cin >> s;
	int i = 0;
	while (s[i]) { // convert to upper case
		s[i] = toupper(s[i]);
		i++;
	}
	cout << s;
}