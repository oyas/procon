// 21:40~
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

typedef pair<int, int> P;

int u[33][33];
P memo[33][33][33][33];
int h, w, s, ming;

struct group{
	int bx, by, ex, ey;
	group(int x, int y, int _x, int _y){
		bx = x;
		by = y;
		ex = _x;
		ey = _y;
	}
};

int calc(int bx, int by, int ex, int ey){
	int sum=0;
	if( bx > ex ) swap( bx, ex );
	if( by > ey ) swap( by, ey );
	for(int y=by; y<ey; y++){
		for(int x=bx; x<ex; x++){
			sum += u[y][x];
		}
	}
	return sum;
}

P solve(int bx, int by, int ex, int ey){
	if( memo[bx][by][ex][ey].first ){
		return memo[bx][by][ex][ey];
	}
	P result(1, calc(bx,by,ex,ey)-ming), tmp;
//	cout << "calc: " << calc(bx,by,ex,ey) << endl;
//	result = max(result, tmp);
	for(int y=by+1; y<ey; y++){
		if( calc(bx,by,ex,y) >= ming &&
			calc(bx,y,ex,ey) >= ming ){
			P t1 = solve(bx,by,ex,y);
			P t2 = solve(bx,y,ex,ey);
			tmp.first = t1.first + t2.first;
			tmp.second = min(t1.second, t2.second);
			result = max(result, tmp);
//	cout << "calc2y: " << calc(bx,by,ex,y)+calc(bx,y,ex,ey) << endl;
//	cout << tmp.first << "  " << tmp.second << endl; 
		}
	}
	for(int x=bx+1; x<ex; x++){
		if( calc(bx,by,x,ey) >= ming &&
			calc(x,by,ex,ey) >= ming ){
			P t1 = solve(bx,by,x,ey);
			P t2 = solve(x,by,ex,ey);
			tmp.first = t1.first + t2.first;
			tmp.second = min(t1.second, t2.second);
			result = max(result, tmp);
//	cout << "calc2x: " << calc(bx,by,x,ey)+calc(x,by,ex,ey) << endl;
//	cout << tmp.first << "  " << tmp.second << endl; 
		}
	}
//	cout << result.first << "  " << result.second << endl; 
	memo[bx][by][ex][ey] = result;
	return result;
}

int main(){
	while(cin >> h >> w >> s, h|w|s){
		int sume=0;//, ans=0;
		fill( memo[0][0][0], memo[0][0][0]+33*33*33*33, P(0,0) );
		for(int y=0; y<h; y++){
			for(int x=0; x<w; x++){
				cin >> u[y][x];
				sume += u[y][x];
			}
		}
		ming = sume - s;
//		cout << "ming: " << ming << endl;
		P ans = solve(0,0,w,h);
//		queue< vector<group> > que;
//		vector<group> grs;
//		grs.push_back( group(0,0,w,h) );
//		que.push( group(0,0,w,h) );
//		while( !que.empty() ){
//			vector<group> grs = que.front();
//			que.pop();
//			for(int i=0; i<grs.size(); i++ ){
//			}
//		}
		cout << ans.first << " " << ans.second << endl;
	}
	return 0;
}
