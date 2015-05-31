// 13:54~ 59~ CodingStart14:13~
#include <iostream>
#include <algorithm>
#include <stack>

using namespace std;

int vx[]={1,0,-1,0}, vy[]={0,1,0,-1};

int h, w, c;

struct map{
	int m[12][12];
	map(){
		fill( m[0], m[0]+12*12, 0 );
	}
};

struct status{
	int to, x, y;
	status(int t, int _x, int _y){
		x = _x;
		y = _y;
		to = t;
	}
};

void calc(int to, map &m){
	stack<status> st;
	st.push( status(to, 1, 1) );
	while(!st.empty()){
		status s = st.top(); st.pop();
		if( m.m[s.x][s.y] > 9 || m.m[s.x][s.y] == to ){
			m.m[s.x][s.y] = to + 10;
			for(int i=0; i<4; i++){
				if( m.m[ s.x+vx[i] ][ s.y+vy[i] ] != to + 10 )
					st.push( status(to, s.x+vx[i], s.y+vy[i]) );
			}
		}
	}
}

int solve(int count, int to, map m){
	int result=0;
	calc(to, m);
	if( count == 4 ){
		calc(c, m);
		for(int i=1; i<=h; i++){
			for(int j=1; j<=w; j++){
				if( m.m[i][j] > 9 )
					result++;
			}
		}
	}else{
		for(int i=1; i<=6; i++){
			if( i != to )
				result = max( result, solve(count+1, i, m) );
		}
	}
	return result;
}

int main(){
	while(cin >> h >> w >> c, h|w|c){
		map m;
		for(int x=1; x<=h; x++){
			for(int y=1; y<=w; y++){
				cin >> m.m[x][y];
			}
		}
		int ans = solve(0, m.m[1][1], m);
		cout << ans << endl;
	}
	return 0;
}
