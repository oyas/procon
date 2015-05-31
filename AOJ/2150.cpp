// 2:13~16~ AC2:42
#include <iostream>
#include <vector>
#include <algorithm>

#define PMAX 200000

using namespace std;

int main(){
	vector<int> prime;
	bool pr[PMAX]={0};
	pr[0] = true; pr[1] = true;
	for(int i=2; i<PMAX; i++){
		if(!pr[i]){
			prime.push_back(i);
			for(int j=2*i; j<PMAX; j+=i){
				pr[j] = true;
			}
		}
	}
	int N, P;
	while(cin >> N >> P, N != -1 && P != -1){
		vector<int> sum;
		int j;
		for(j=0; j<prime.size(); j++){
			if( prime[j] > N ){
				break;
			}
		}
		for(int i=0; i<P; i++){
			for(int k=0; k<=i; k++){
				sum.push_back( prime[j+i] + prime[j+k] );
			}
		}
		sort(sum.begin(), sum.end());
		cout << sum[P-1] << endl;
	}
	return 0;
}
