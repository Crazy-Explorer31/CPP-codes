#include <iostream>
using namespace std;
void print_string(int n, int k) {
	for (int i = 0; i < k; i++) {
		cout<<' ';
	}
	cout<<'M';
	for (int i = 0; i < n - 1 - k; i++) {
		cout<<"OM";
	}
	cout<<endl;
}

int main(){
	int n;
	cin>>n;
	for (int k = n - 1; k >= 0; k--) {
		print_string(n, k);
	}
    return 0;
}