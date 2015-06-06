// 14:55~ 15:30
#include <iostream>
#include <map>

using namespace std;

int main(){
	int N;
	while(cin>>N, N){
		map<int, int> m;
		map<int, int>::iterator it;
		m.insert( make_pair(0, -1) );
		m.insert( make_pair(1000000001, -2) );
		while(N--){
			char com;
			int I, S, P, ans=-1;
			cin >> com;
			switch(com){
			case 'W':
				cin >> I >> S;
				for(it = m.begin(); it!=m.end() && S;){
					if(it->second == -1){
						it->second = I;
						int st = it->first;
						it++;
						int ls = it->first;
						if( ls-st > S ){
							m.insert( make_pair(st+S, -1) );
							break;
						}else{
							S -= ls-st;
						}
					}else it++;
				}
				break;
			case 'D':
				cin >> I;
				for(it = m.begin(); it!=m.end(); it++){
					if( it->second == I ){
						it->second = -1;
					}
				}
				break;
			case 'R':
				cin >> P;
				for(it = m.begin(); it!=m.end(); it++){
					if( it->first > P ){
						break;
					}else{
						ans = it->second;
					}
				}
				cout << ans << endl;
				break;
			}
		}
		cout << endl;
	}
	return 0;
}
