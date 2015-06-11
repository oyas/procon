#include <iostream>
#include <vector>
#include <set>
#include <stack>

#define INF 0x3fffffff

using namespace std;

int main(){
	int n;
	while(cin>>n, n){
		int to[900], ds[900], to_num[900]={0}, ds_sum=0, ans=0;
		int w[900][900];
		set<int> sg;
		vector<int> tosg[900], dssg[900];
		fill( w[0], w[0]+900*900, INF );
		for(int i=1; i<n; i++){
			cin >> to[i];
			to[i]--;
			to_num[ to[i] ]++;
			to_num[ i ]++;
		}
		for(int i=1; i<n; i++){
			cin >> ds[i];
			ds_sum += ds[i];
			if( to[i] == 0 ){
				to[0] = i;
				ds[0] = ds[i];
			}
		}

		// 葉の部分を求める
		int ds_ha = 0;
		for(int i=0; i<n; i++){
			if( to_num[i] == 1 ){
				ds_ha += ds[i]; 
				sg.insert( to[i] );
			}
		}

		// 木の直径
		for(int i=1; i<n; i++){
			int j = to[i], sum = ds[i];
			if( sg.count(i) )
				while(1){
					w[i][j] = min( w[i][j], sum);
					w[j][i] = min( w[j][i], sum);
					for(int k=0; k<tosg[j].size(); k++){
						w[i][ tosg[j][k] ] = min(w[i][ tosg[j][k] ], sum + dssg[j][k]);
						w[ tosg[j][k] ][i] = min(w[i][ tosg[j][k] ], sum + dssg[j][k]);
					}
					tosg[j].push_back( i );
					dssg[j].push_back( sum );
					if( j == 0 ) break;
					else {
						sum += ds[j];
						j = to[j];
					}
				}
		}
		int maxlen=0;
		for(int i=0; i<n; i++){
			for(int j=0; j<i; j++){
				if( sg.count(i) && sg.count(j) && w[i][j] < INF ){
					maxlen = max( maxlen, w[i][j] );
				}
			}
		}

		// 出力
		ans = (3 * ds_sum) - (2 * ds_ha) - maxlen;
		//	cout << ds_sum << " " << ds_ha << " " << maxlen << endl;
		cout << ans << endl;
	}
	return 0;
}
