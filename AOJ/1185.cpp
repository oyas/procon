#include <iostream>
#include <algorithm>

#define INF 0x7fffffff

using namespace std;

int h, w;

int solve( char str[100][100] ){
	int x=-1, y, sum=INF;
	for(int i=0; i<h && x==-1; i++){
		for(int j=0; j<w; j++){
			if( str[i][j] == '#' ){
				x = j;
				y = i;
				break;
			}
		}
	}
//	cout << "x=" << x << " y=" << y << endl;
	if( x == -1 ) return 0;
	//set
	char cstr[100][100];
	for(int k=0; k<h; k++){
		for(int l=0; l<w; l++){
			cstr[k][l] = str[k][l];
		}
	}
	for(int i=y; i<h; i++){
		int j;
		for(j=x; j<w; j++){
			int k=y;
			for(; k<=i; k++){
				if( str[k][j] == '.' )
					break;
			}
			if( k<=i ) break;
			for(k=y; k<=i; k++){
				cstr[k][j] = '.';
			}
			sum = min(sum, solve(cstr) );
		}
		//戻す
		for(int k=y; k<=i; k++){
			for(int l=x; l<=j; l++){
				cstr[k][l] = str[k][l];
			}
		}
	}
	return sum+1;
}

int main(){
	while(1){
		cin >> h >> w;
		if( !(h | w) )
			break;
		
		char str[100][100];
		for(int i=0; i<h; i++){
			cin >> str[i];
		}
		
		cout << solve( str ) << endl;
	}
	return 0;
}
