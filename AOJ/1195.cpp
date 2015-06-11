// 17:20~ 19:24
#include <iostream>
#include <string>
#include <set>

using namespace std;

set<string> ans;
bool noans;

void solve(char a, string &str, int r = -1){
//	cout << "solve: " << str << " " << a << r << endl;
	if( a == 'a' ){
		ans.insert( str );
		return;
	}
	a--;
	int f = -1, count=0, countnow=0;
	for(int i=0; i<str.length(); i++){
		if( str[i] == a+1 ){
			count++;
			if( count > 1 && countnow == 0 ){
				noans = true;
				return;
			}
		}
		if( str[i] == a ){
			countnow++;
			if( (r == -1 || r > i )&& count == 0){
				if( f < 0 ){
					f = i;
				}else if( a < 'z' ){
					solve( a, str, f );
				}
				if( a < 'z' ){
					string tmp = str;
					tmp[i] = a+1;
					solve( a, tmp );
				}
			}
		}
	}
	if( r<0 )
		solve( a, str, f );
}

int main(){
	string str;
	set<string>::iterator it;
	while(cin>>str, str[0] != '#'){
		ans.clear();
		noans = false;
		// 解く
		solve( 'z'+1, str );
		// 出力
		if( noans ){
			cout << 0 << endl;
			continue;
		}
		cout << ans.size() << endl;
		if( ans.size() <= 10 ){
			for(it = ans.begin(); it != ans.end(); it++){
				cout << *it << endl;
			}
		}else{
			int count=0;
			for(it = ans.begin(); count < 5; it++, count++){
				cout << *it << endl;
			}
			for(it = ans.end(); count > 0; it--, count--){}
			for(; count < 5; it++, count++){
				cout << *it << endl;
			}
		}
	}
	return 0;
}
