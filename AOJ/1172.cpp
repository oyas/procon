// 13:00~ 05~ AC13:16
#include <iostream>
#include <vector>

#define PMAX 323456

using namespace std;

int main(){
	vector<int> prime;
	bool pr[PMAX]={0};
	pr[0] = pr[1] = true;
	for(int i=0; i<PMAX; i++){
		if( !pr[i] ){
			prime.push_back(i);
			for(int j=2*i; j<PMAX; j+=i)
				pr[j] = true;
		}
	}
	int n;
	while( cin >> n, n){
		int ans=0;
		for(int i=0; i<prime.size(); i++){
			if( n < prime[i] && prime[i] <= 2*n )
				ans++;
		}
		cout << ans << endl;
	}
	return 0;
}
