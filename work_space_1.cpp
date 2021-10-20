#include <iostream>
using namespace std;

int main(){
	int n;
	cin>>n;
	int ratings[n];
	for (int i = 0; i < n; i++) {
		cin>>ratings[i];
	}
	int res = 0;
	bool flag = false;
	for (int i = 0; i < n - 1; i++) {
		for (int j = i + 1; j < n; j++) {
			if (ratings[i] % 2 == 0 && ratings[j] % 2 == 0 && flag && ratings[i] > ratings[j]) {
				res++;
			}
			if (ratings[j] % 2 != 0) {
				flag = true;
			}
		}
		flag = false;
	}
	cout<<res;
    return 0;
}