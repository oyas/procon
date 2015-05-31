// 15:29~ 33~ 
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <queue>

using namespace std;

struct E{
	vector<int> ov;
	int color;
	int x, y, r;
	E(int _x, int _y, int _r, int _c){
		color = _c;
		x = _x;
		y = _y;
		r = _r;
	}
};

bool dp[(1<<25)] = {0};
int main(){
	int n;
	while(cin >> n, n){
		int x, y, r, c, _ans=0;
		vector<E> e;
		queue<int> que;
		for(int i=0; i<n; i++){
			cin >> x >> y >> r >> c;
			E tmp(x,y,r,c);
			for(int j=0; j<e.size(); j++){
				if( (e[j].x-x)*(e[j].x-x) + (e[j].y-y)*(e[j].y-y) < (e[j].r+r)*(e[j].r+r) ){
					tmp.ov.push_back( j );
				}
			}
			e.push_back( tmp );
		}
		fill(dp, dp+(1<<25), false);
		dp[0] = true;
		que.push(0);
		int ans=0;
		while( !que.empty() ){
			int i = que.front();
			que.pop();
			if(dp[i]){
			//	dp[i] = true;
		//		_ans = max(_ans,i);
				_ans = 0;
				for(int v=1; v<(1<<n); v<<=1){
					if( v & i )
						_ans++;
				}
				ans = max(ans, _ans);
				for(int k=0; k<n; k++){
					for(int l=0; l<k; l++){
						if( k != l && !(i&(1<<k)) && !(i&(1<<l)) && e[k].color == e[l].color){
							bool f=true;
							for(int j=0; j<e[k].ov.size(); j++){
								if( !(i & (1<<e[k].ov[j])) ){
									f=false;
									break;
								}
							}
							for(int j=0; f&&j<e[l].ov.size(); j++){
								if( !(i & (1<<e[l].ov[j])) ){
									f=false;
									break;
								}
							}
							if( f ){
								if( !dp[ i | (1<<k) | (1<<l) ] ){
									dp[ i | (1<<k) | (1<<l) ] = true;
									que.push( i | (1<<k) | (1<<l) );
								}
							}
						}
					}
				}
			}
		}
		cout << ans << endl;
	}
	return 0;
}
