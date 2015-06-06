// 22:23~ 37~ AC23:58
#include <iostream>
#include <algorithm>

#define INF 0x3fffffff

#define REP(i, n) for(int (i)=0; (i)<(n); (i)++)

using namespace std;

int main(){
	int n, m, c, s, g;
	while(cin>>n>>m>>c>>s>>g, n|m|c|s|g){
		int x, y, d, cm, p[25];
		int w[25][105][105];
		int road[105][105];
		fill(w[0][0], w[0][0]+25*105*105, INF);
		fill(road[0], road[0]+105*105, INF);
		for(int i=0; i<m; i++){
			cin >> x >> y >> d >> cm;
			w[cm-1][x][y] = min( w[cm-1][x][y], d);
			w[cm-1][y][x] = min( w[cm-1][y][x], d);
		}
		// ワーシャルフロイド
		REP(l, c) REP(k, n+1) REP(i, n+1) REP(j, n+1){
			w[l][i][j] = min(w[l][i][j], w[l][i][k] + w[l][k][j]);
		}
		// 料金
		REP(i, c) cin >> p[i];
		REP(i, c){
			int q[50]={0}, r[50];
			REP(j, p[i]-1) cin >> q[j+1];
			REP(j, p[i]) cin >> r[j];
//			cout << "計算" << endl;
			int now=0, rlas=r[p[i]-1], cha[10000]={0};
			REP(j, 10000){
				if( now+1 < p[i] && j >= q[now+1] ){
					now++;
				}
				cha[j+1] = cha[j] + r[now];
			}
			// road[][]に代入
			REP(j, n+1) REP(k, j){
				int len = w[i][j][k];
				if( len == INF ) continue;
				int sum = (len>10000)?(cha[10000]+rlas*(len-10000)):(cha[len]);
				road[j][k] = min(road[j][k], sum);
				road[k][j] = min(road[k][j], sum);
			}
		}
		// ワーシャルフロイド
		REP(k, n+1) REP(i, n+1) REP(j, n+1){
			road[i][j] = min(road[i][j], road[i][k] + road[k][j]);
		}
		// 出力
		if( road[s][g] >= INF )
			cout << -1 << endl;
		else
			cout << road[s][g] << endl;
	}
	return 0;
}
