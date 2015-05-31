#include <iostream>

using namespace std;

char room[2][100][100];
int vx[] = {1, 0, -1, 0}, vy[] = {0, 1, 0, -1};

bool solve(const int pos[2][2]){
	if(pos[0][0] < 0 ||
		pos[0][1] < 0 ||
		pos[1][0] < 0 ||
		pos[1][1] < 0 ||
		pos[0][0] > 60 ||
		pos[0][1] > 60 ||
		pos[1][0] > 60 ||
		pos[1][1] > 60 ){
		cout << "error" << endl;
		return true;
	}
	if( room[0][pos[0][0]][pos[0][1]] == '#' ||
		room[1][pos[1][0]][pos[1][1]] == '#' ){
		cout << "error" << endl;
		return false;
	}
//	cout << "s()" << pos[1][1];
	int nextpos[2][2];
	for(int i=0; i<4; i++){
		nextpos[0][0] = pos[0][0]+vy[i];
		nextpos[0][1] = pos[0][1]+vx[i];
		nextpos[1][0] = pos[1][0]+vy[i];
		nextpos[1][1] = pos[1][1]-vx[i];
	if( nextpos[0][0] < 0 ||
		nextpos[0][1] < 0 ||
		nextpos[1][0] < 0 ||
		nextpos[1][1] < 0 ||
		nextpos[0][0] > 60 ||
		nextpos[0][1] > 60 ||
		nextpos[1][0] > 60 ||
		nextpos[1][1] > 60 ){
		cout << "error" << endl;
		return true;
	}
		if( 	room[0][pos[0][0]+vy[i]][pos[0][1]+vx[i]] == '#' &&
				room[1][pos[1][0]+vy[i]][pos[1][1]-vx[i]] != '#' ){
			nextpos[0][0] = pos[0][0];
			nextpos[0][1] = pos[0][1];
		}else if( 	room[0][pos[0][0]+vy[i]][pos[0][1]+vx[i]] != '#' &&
					room[1][pos[1][0]+vy[i]][pos[1][1]-vx[i]] == '#' ){
			nextpos[1][0] = pos[1][0];
			nextpos[1][1] = pos[1][1];
		}else if( 	room[0][pos[0][0]+vy[i]][pos[0][1]+vx[i]] == '#' &&
					room[1][pos[1][0]+vy[i]][pos[1][1]-vx[i]] == '#' ){
			continue;
		}else if( 	room[0][pos[0][0]+vy[i]][pos[0][1]+vx[i]] == '%' ||
					room[1][pos[1][0]+vy[i]][pos[1][1]-vx[i]] == '%' ){
			return (room[0][pos[0][0]+vy[i]][pos[0][1]+vx[i]] == '%' &&
					room[1][pos[1][0]+vy[i]][pos[1][1]-vx[i]] == '%' );
		}
		if( room[0][nextpos[0][0]][nextpos[0][1]] == '.' &&
			room[1][nextpos[1][0]][nextpos[1][1]] == '.' )
		if( solve(nextpos) )
			return true;
	}
	return false;
}

int main(){
	int W, H;
	
	while(cin >> W >> H, W|H){
		fill(room[0][0], room[0][0]+100*100*2, '#');
		int initpos[2][2]={0};
		for(int i=1; i<=H; i++){
			for(int k=0; k<2; k++)
			for(int j=1; j<=W; j++){
				cin >> room[k][i][j];
				if(room[k][i][j] == 'L' || room[k][i][j] == 'R'){
					initpos[k][0] = i;
					initpos[k][1] = j;
				}
			}
		}
		cout << (solve(initpos)?"Yes":"No") << endl;
	}
	return 0;
}
