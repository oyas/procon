// 20:30-
#include <iostream>
#include <cmath>
#include <algorithm>

#define FMAX 1000006

using namespace std;


int pos[2]={500,500};
void toXY(int i, int &p_num, int &x, int &y){
	int pp_num = p_num*p_num;
	while( i > pp_num ){
		pos[0]++; pos[1]++;
		p_num+=2;
		pp_num = p_num*p_num;
	}
	if( pp_num - p_num < i ){
		x = pos[0] - pp_num + i;
		y = pos[1];
	}else if( pp_num - 2*(p_num-1) <= i ){
		x = pos[0] - p_num + 1;
		y = pos[1] - (pp_num - i - p_num + 1 );
	}else if( pp_num - 3*(p_num-1) <= i ){
		x = pos[0] + (pp_num - 3*(p_num-1) - i );
		y = pos[1] - p_num + 1;
	}else{
		x = pos[0];
		y = pos[1] + (pp_num - 4*(p_num-1) - i );
	}
	//cout << "i=" << i << " x=" << x << " y=" << y << endl;
}

int toNum(int x, int y){
	int r = max(abs(x-500), abs(y-500) );
	if( r == 0 ) return 1;
	int n = 1 + 2*r;
//	cout << x << " " << y << " n=" << n << endl;
	int ret = n*n;
	if( 500+r == x && 500+r == y ){
	}else if( 500+r == x ){
		ret = (n-2)*(n-2) + 500+r - y;
	}else if( 500-r == y ){
		ret -= 2*(n-1) + x - (500-r);
	}else if( 500-r == x ){
		ret -= n-1 + 500+r - y;
	}else if( 500+r == y ){
		ret -= 500+r - x;
	}
	return ret;
}

bool dou[1005][1005]={0};
int dp[1005][1005], ans[1005][2]={0};

int main(){
	int m, n;
	bool f[FMAX]={0};
	int p_num=1;

	fill(f, f+FMAX, true);
	f[0]=false;f[0]=false;
	for(int i=2; i<FMAX; i++){
		if( f[i] ){
			for(int j=i*2; j<FMAX; j+=i ){
				f[j] = false;
			}
			int x, y;
			toXY(i, p_num, x, y);
			dou[x][y] = true;
		}
	}

	while(1){
		cin >> m >> n;
		if( !(m | n) )
			break;
		
		int x, y;
		fill( dp[0], dp[0]+1005*1005, -1 );
		fill( ans[0], ans[0]+1005*2, 0 );
		p_num = 1; pos[0]=500; pos[1]=500;
		toXY(n, p_num, x, y);
		cout << "toXY = " << x << " " << y << endl;
		dp[x][y] = dou[x][y];
		if(dou[x][y]){
			ans[x][0]=1;
			ans[x][1]=n;
		}
		for(int i=y; i<2000;i++){
			for(int j=1;j<1001;j++){
//				cout << "toNum " << toNum(j,i) << endl;
				if( toNum(j, i) > m ){
					if( toNum(500, i) > m ){
						i = 3000;
						break;
					}
					continue;
				}
				if( dp[j][i] == -1 )
					continue;
				for(int k=-1; k<2; k++){
					if( toNum(j+k, i+1) > m ){
						continue;
					}
					if( dp[j][i] + dou[j+k][i+1] > dp[j+k][i+1] ){
						dp[j+k][i+1] = dp[j][i] + dou[j+k][i+1];
						if( dou[j+k][i+1] ){
							ans[j+k][0] = dp[j+k][i+1];
							ans[j+k][1] = toNum(j+k, i+1);
						}
					}
				}
			}
		}
		int a=0;
		for(int i=0; i<1003; i++){
			if( ans[a][0] < ans[i][0] ||
					(ans[a][0] == ans[i][0] && ans[a][1] < ans[i][1]) ){
				a = i;
			}
		}
		cout << ans[a][0] << " " << ans[a][1] << endl;
	}
	return 0;
}
