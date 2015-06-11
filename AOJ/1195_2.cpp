// 19:34~
#include <iostream>
#include <string>
#include <set>

using namespace std;

string str;

bool check(int k){
	int count[256] = {0}, d = 0;
	count['a'] = count['z'+1] = 1;
	for(int i=0; i<str.length(); i++){
		if( !count[ str[i] + ((k&(1<<i))?1:0) ]++ )
			d |= (1<<i);
	}
	return k == d;
}

int main(){
	while(cin >> str, str[0] != '#'){
		set<string> ans;
		set<string>::iterator it;
		for(int k=0; k<(1<<str.length()); k++){
			if( check(k) ){
				string str2 = str;
				for(int l=0; l<str.length(); l++){
					if( k & (1<<l) && str[l] != 'z' ){
						str2[l]++;
					}
				}
				ans.insert( str2 );
			}
		}
		// 出力
		cout << ans.size() << endl;
		if( ans.size() <= 10 ){
			for(it = ans.begin(); it != ans.end(); it++)
				cout << *it << endl;
		}else{
			int count = 0;
			for(it = ans.begin(); count < 5; it++, count++)
				cout << *it << endl;
			for(it = ans.end(); count > 0; it--, count--){}
			for(; count < 5; it++, count++)
				cout << *it << endl;
		}
	}
}
