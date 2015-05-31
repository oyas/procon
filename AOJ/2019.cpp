#include <iostream>
#include <algorithm>

using namespace std;

int main(){
	int N, M, D[10005], P[10005];
	while( cin >> N >> M, N|M ){
		for(int i=0; i<N; i++){
			cin >> D[i] >> P[i];
		}
		for(int i=0; i<N; i++){
			for(int j=1; j<N; j++){
				if( P[j-1] < P[j] ){
					int tmp = P[j-1];
					P[j-1] = P[j];
					P[j] = tmp;
					tmp = D[j-1];
					D[j-1] = D[j];
					D[j] = tmp;
				}
			}
		}
		int ans=0;
		for(int i=0; i<N; i++){
			if( M>0 ){
				ans += max(0, D[i]-M) * P[i];
				M -= D[i];
			}else{
				ans += D[i] * P[i];
			}
		}
		cout << ans << endl;
	}
	return 0;
}
