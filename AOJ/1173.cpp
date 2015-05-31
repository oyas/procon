// 13:16~ RE13:37 AC13:54
#include <iostream>
#include <cstdio>
#include <vector>
#include <stack>

using namespace std;

int main(){
	int rk=0, sk=0, len=0;
	char in;
	bool check=false;
	vector<char> st;
	st.push_back(' ');
	while(true){
		scanf("%c", &in);
		if( in == '\n' ) continue;
		if( in == '.' && len == 0 ) break;
		len++;
		if( in == '(' ){ rk++; st.push_back('('); }
		if( in == '[' ){ sk++; st.push_back('['); }
		if( in == ')' ){
			if( --rk < 0 || st.empty() || st.back() != '(' ){
				check=true;
				st.push_back(' ');
			}
			st.pop_back();
		}
		if( in == ']' ){
			if( --sk < 0 || st.empty() || st.back() != '[' ){
				check=true;
				st.push_back(' ');
			}
			st.pop_back();
		}
		if( in == '.' ){
			if( rk != 0 || sk != 0 )
				check = true;
			cout << (check?"no":"yes") << endl;
			rk = 0;
			sk = 0;
			len = 0;
			check = false;
			st.clear();
			st.push_back(' ');
		//	while(st.empty()) st.pop();
		//	st.push(' ');
		}
	}
	return 0;
}
