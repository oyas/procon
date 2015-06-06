// 17:30~ 22:30
#include <cstdio>
#include <iostream>
#include <cmath>

#define INF 1000000.0

using namespace std;

struct P{
	double x, y;
	P(double X=0.0, double Y=0.0){
		x = X;
		y = Y;
	} 
	P operator+( const P &in ){
		P tmp( x + in.x , y + in.y );
		return tmp;
	}
	P operator-( const P &in ){
		P tmp( x - in.x , y - in.y );
		return tmp;
	}
	P operator*( const double &in ){
		P tmp( x * in , y * in );
		return tmp;
	}
	double dot( const P &in ){
		return x * in.x + y * in.y;
	}
	double cross( const P &in ){
		return x * in.y - y * in.x;
	}
	double length(){
		return sqrt( x*x + y*y );
	}
};


//交差しているか求める(どの3点も同直線上にない)
bool check(P a1, P a2, P b1, P b2){
	P va = a2 - a1, vb = b2 - b1;
	P v1 = b1 - a1, v2 = b2 - a2;

	if( ( va.cross( v1 ) * va.cross( v2 ) ) < 0.0 &&
		( vb.cross( v1 ) * vb.cross( v2 ) ) < 0.0 )
		return true;
	
	return false;
}

//2円の交点を求める(2円の中心の中点cからのベクトルvを返す(交点はc±v) )
void circlecross(P a, double ra, P b, double rb, P *p1, P *p2){

	double c = (a - b).length();
	double r = (ra*ra - rb*rb + c*c ) / ( 2.0 * c*c );
	double d = sqrt( ra*ra - c*c*r*r );
	
	P tmp( d*(a.y - b.y)/c, d*(b.x - a.x)/c);
	P cen = a * (1.0-r) + b * r;
	
	*p1 = cen + tmp;
	*p2 = cen - tmp;
}

int n;

int solve(){
	P c[100], p[101][2];
	double r[100];
	double dist[205][205];
	
	cin >> c[0].x >> c[0].y >> r[0];
	p[0][0] = c[0];
	p[0][1] = c[0];
	for(int i=1; i<n; i++){
		cin >> c[i].x >> c[i].y >> r[i];
		circlecross( c[i-1], r[i-1], c[i], r[i], &p[i][0], &p[i][1]);
	}
	p[n][0] = c[n-1];
	p[n][1] = c[n-1];

	//求める
	fill( dist[0], dist[0]+205*205, INF );
	for(int i=0; i<n*2; i++){
		for(int j=i+1; j<=n*2; j++){
			bool f=true;
			for(int k=i/2+1; k<j/2; k++){
				if( !check( p[i/2][i%2], p[j/2][j%2], p[k][0], p[k][1] ) )
					f = false;
			}
			if( f ){
				double x = p[i/2][i%2].x - p[j/2][j%2].x;
				double y = p[i/2][i%2].y - p[j/2][j%2].y;
				dist[i][j] = sqrt( x*x + y*y );
			}
		}
	}
	//最短経路
	for(int k=1; k<n*2; k++){
		for(int i=0; i<=n*2; i++){
			for(int j=0; j<=n*2; j++){
				dist[i][j] = min( dist[i][j], dist[i][k] + dist[k][j] );
			}
		}
	}

	printf("%0.6f\n", dist[0][n*2] );
	
	return 0;
}

int main(){
	while( cin >> n, n ){
		solve();
	}
	return 0;
}
