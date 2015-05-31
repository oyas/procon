#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

int n, dp[1<<25]={0};

int solve(){
	vector<int> pile[24];
	int x[24], y[24], r[24], c[24];

	for(int i=0; i<n; i++){
		cin >> x[i] >> y[i] >> r[i] >> c[i];
		for(int j=0; j<i; j++){
			if( sqrt( (x[i]-x[j])*(x[i]*x[j]) + (y[i]-y[j])*(y[i]-y[j]) )
					< r[i] + r[j] ){
				pile[j].push_back( (1<<i) );
			}
		}
	}
	for(int i=0; i<(1<<n); i++){
		for(int j=0; j<n; j++){
			if( !( i&(1<<j) ) ) continue;
			int p=0;
			for(; p<pile[j].size(); p++ ){
				if( pile[j][p] & i )
					break;
			}
			if( p != pile[j].size() ) continue;
			for(int k=0; k<j; k++){
				if( !( i&(1<<k) ) ) continue;
				if( c[j] != c[k] ) continue;
				for(p=0; p<pile[k].size(); p++ ){
					if( pile[k][p] & i )
						break;
				}
				if( p != pile[k].size() ) continue;
				
				//取り除ける
				dp[i] = max( dp[i], 2 + dp[ i^( (1<<j) | (1<<k) ) ] );
			}
		}
	}

	cout << dp[(1<<n)-1] << endl;

	return 0;
}

int main(){
	while(1){
		cin >> n;
		if(n==0) break;
		solve();
	}
}
