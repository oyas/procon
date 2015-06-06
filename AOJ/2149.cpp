// 14:15~ 14:27
#include <iostream>

using namespace std;

int main(){
	int N, A, B, C, X;
	while(cin>>N>>A>>B>>C>>X, N|A|B|C|X){
		int Y, f=0, fir=1;
		for(int i=0; i<N; i++){
			cin >> Y;
			for(;(X!=Y||!fir) && f<=10000 ;f++, fir++){
				X = (A*X+B) % C;
			}
			fir=0;
		}
		if( f<=10000 ) cout << f << endl;
		else cout << -1 << endl;
	}
	return 0;
}
