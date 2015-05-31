#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

#define INF 0x7fffffff

using namespace std;

typedef pair<int, pair<int,int> > PP;

struct edge{
	int to, D, E;
	edge(int t, int d, int e): to(t), D(d), E(e) {}
};


int main(){
	int N, M, L, A, B, D, E;

	while( cin>>N>>M>>L, N|M|L ){
		priority_queue<PP,vector<PP>,greater<PP> > que;
		vector<edge> v[105];
		int dh[105][105];

		for(int i=0; i<M; i++){
			cin >> A >> B >> D >> E;
			v[A].push_back( edge(B, D, E) );
			v[B].push_back( edge(A, D, E) );
		}
		fill(dh[0], dh[0]+105*105, INF);
	
		// ダイクストラ
		que.push( make_pair(0, make_pair(1,L)) );
		while( !que.empty() ){
			PP p = que.top(); que.pop();
			int psf = p.second.first, pss = p.second.second;
			// 取り出す時チェック→ push時にチェックに変えると高速化できる
			if( pss >= 0 && p.first < dh[psf][pss] ){
				dh[psf][pss] = p.first;
				for(int i=0; i<v[psf].size(); i++){
					edge e = v[psf][i];
					que.push( make_pair(p.first + e.E, make_pair(e.to, pss)) );
					que.push( make_pair(p.first, make_pair(e.to, pss-e.D)) );
				}
			}
		}

		int ans = INF;
		for(int i=0; i<=L; i++)
			ans = min(ans, dh[N][i] );

		cout << ans << endl;
	}
	return 0;
}
