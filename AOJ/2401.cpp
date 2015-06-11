// 2:22~ 2:54
#include <iostream>
#include <string>

using namespace std;

bool eval(int val, string str, int &i){
	if( 'a' <= str[i] && str[i] <= 'k' ){
		return val & (1<<(str[i++]-'a'));
	}else if( str[i] == 'T' ){
		return true;
	}else if( str[i] == 'F' ){
		return false;
	}else if( str[i] == '-' && str[i+1] != '>' ){
		return !eval(val, str, ++i);
	}else if( str[i] == '(' ){
		bool ret = eval(val, str, ++i);
		while( i<str.length() ){
			if( str[i] == '+' ) ret |= eval(val, str, ++i);
			else if( str[i] == '*' ) ret &= eval(val, str, ++i);
			else if( str[i] == '-' && str[i+1] == '>'){
				i++;
				ret = !ret | eval(val, str, ++i);
			}
			else if( str[i] == ')' ) break;
			else i++;
		}
		i++;
		return ret;
	}
	return false;
}

int main(){
	string in;
	while(cin>>in, in[0]!='#'){
		string str1 = "(" + in.substr(0, in.find("=")) + ")";
		string str2 = "(" + in.substr(in.find("=")+1) + ")";
		bool f = true;
		for(int val=0, i=0, j=0; val<(1<<11); val++, i=0, j=0){
			if( eval(val, str1, i) != eval(val, str2, j) )
				f = false;
		}
		cout << (f?"YES":"NO") << endl;
	}
	return 0;
}
