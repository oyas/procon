// 2回目 23:15~ AC23:45
// AOJ1174
// この問題は再帰で解けるが、下手をするとスタックオーバーフローになるのでスタックと構造体で解く方も書いてみた。
#include <iostream>
#include <algorithm>
#include <vector>
#include <stack>

using namespace std;

typedef pair<int, int> P;

int vx[]={1,0,-1,0}, vy[]={0,1,0,-1};

// 状態を保持する構造体
struct status{
	int count, to;
	int p[10][10];
	status(int c=0, int t=0, status *old=NULL){	//コンストラクタで全ての値をセットできるようにしておく
		if( old ) *this = *old;		// 全コピー(memcpy()より楽で間違いが少ない)
		else fill(p[0], p[0]+10*10, 0);	//メンバ配列の初期化はコンストラクタで
		count = c;
		to = t;
	}
};

int main(){
	int h, w, c;
	while(cin>>h>>w>>c, h|w|c){
		// 初期化でバグるからほとんどの変数はここで定義
		stack<status> st;
		int ans = 0;
		
		// 初期値セット
		status in;
		for(int i=1; i<=h; i++){
			for(int j=1; j<=w; j++){
				cin >> in.p[i][j];
			}
		}
		in.to = in.p[1][1];
		in.p[1][1] = 8;
		
		// 深さ優先探索
		st.push( in );
		while( !st.empty() ){
			status s = st.top(); st.pop();
			// s.toに色を変更
			vector< P > check;	//stackでもよかったがansの数え上げに使えたからvectorに変更
			for(int i=1; i<=h; i++){	// (1,1)と同じ色8の部分を探す
				for(int j=1; j<=w; j++){
					if( s.p[i][j] == 8 )
						check.push_back( make_pair(i, j) );
				}
			}
			for( int i=0; i<check.size(); i++ ){	// 隣接部分の塗替え
				int y = check[i].first, x = check[i].second;
				for(int k=0; k<4; k++){
					if( s.p[ y+vy[k] ][ x+vx[k] ] == s.to ){
						s.p[ y+vy[k] ][ x+vx[k] ] = 8;
						check.push_back( make_pair( y+vy[k], x+vx[k] ) );
					}
				}
			}
			// 次のスタックを積む
			if( s.count == 5 ){		// おわり
				ans = max( ans, (int)check.size() );	//最大サイズ更新
			}else if( s.count == 4 ){
				st.push( status(s.count+1, c, &s) );
			}else{
				for(int i=1; i<=6; i++){
					if( i != s.to ){
						st.push( status(s.count+1, i, &s) );
					}
				}
			}
		}
		
		// 出力
		cout << ans << endl;
	}
	return 0;
}
