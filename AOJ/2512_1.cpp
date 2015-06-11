#include <iostream>
#include <string>

#define INF 0x3fffffff

using namespace std;

struct result {
	int value, p;
	result(int v, int _p): value(v), p(_p) {}
};

result faor(const string &s, int p = 0);
result faxor(const string &s, int p = 0);
result faand(const string &s, int p = 0);
result fapla(const string &s, int p = 0);
result famin(const string &s, int p = 0);
result famul(const string &s, int p = 0);
result term(const string &s, int p = 0);

result faor(const string &s, int p) {
	result r = faxor(s, p);
	while (s[r.p] == '|') {
		result r_ = faxor(s, r.p+1);
		r.value |= r_.value;
		r.p      = r_.p;
	}
	return r;
}
result faxor(const string &s, int p) {
	result r = faand(s, p);
	while (s[r.p] == '^') {
		result r_ = faand(s, r.p+1);
		r.value ^= r_.value;
		r.p      = r_.p;
	}
	return r;
}
result faand(const string &s, int p) {
	result r = fapla(s, p);
	while (s[r.p] == '&') {
		result r_ = faand(s, r.p+1);
		r.value &= r_.value;
		r.p      = r_.p;
	}
	return r;
}
result fapla(const string &s, int p) {
	result r = famin(s, p);
	while (s[r.p] == '+') {
		result r_ = famin(s, r.p+1);
		r.value += r_.value;
		r.p      = r_.p;
	}
	return r;
}
result famin(const string &s, int p) {
	result r = famul(s, p);
	while (s[r.p] == '-') {
		result r_ = famul(s, r.p+1);
		r.value -= r_.value;
		r.p      = r_.p;
	}
	return r;
}
result famul(const string &s, int p) {
	result r = term(s, p);
	while (s[r.p] == '*') {
		result r_ = term(s, r.p+1);
		r.value *= r_.value;
		r.p      = r_.p;
	}
	return r;
}
result term(const string &s, int p) {
	if (s[p] == '(') {
		result r = faor(s, p+1);
		r.p += 1; // skip ')'
		return r;
	} else {
		int value = 0;
		while (isdigit(s[p]))
			value = value * 10 + (s[p++] - '0');
		return result(value, p);
	}
}

string cs = "|^&+-*";

int calc(string exp, int sign=1){
	int ans = -INF;
	for(int i=0; i<=exp.length(); i++){
		for(char j='0'; j<='9'; j++){
			string newexp = exp.substr(0, i) + j + exp.substr(i);
			if( j == '0' && (i == 0 || !isdigit(exp.at(i-1)) ) )
				continue;
			result r = faor( newexp );
			ans = max(ans, r.value * sign);
	//		cout << "n:" << newexp << " r:" << r.value << endl;
		}
		for(int j=0; j<cs.length(); j++){
			string newexp = exp.substr(0, i) + cs.at(j) + exp.substr(i);
			if( i != 0 && i != exp.length() && string::npos == cs.find( exp.at(i-1) ) && string::npos == cs.find( exp.at(i) ) ){
				result r = faor( newexp );
				ans = max(ans, r.value * sign);
	//			cout << "n:" << newexp << " r:" << r.value << endl;
			}
		}
		if( i != exp.length() ){
			string newexp;
			newexp = exp.substr(0, i) + exp.substr(i+1);
			if( (i==0 || string::npos != cs.find(exp.at(i-1)) ) && ( i==exp.length()-1 || string::npos != cs.find(exp.at(i+1)) || exp.at(i+1) == '0' ) )
				continue;
			result r = faor( newexp );
			ans = max(ans, r.value * sign);
		}
	}
	return ans * sign;
}
int calc2(string exp, int sign=1){
	int ans = -INF;
	for(int i=0; i<=exp.length(); i++){
		string newexp;
		int r;
		for(char j='0'; j<='9'; j++){
			newexp = exp.substr(0, i) + j + exp.substr(i);
			if( j == '0' && (i == 0 || !isdigit(exp.at(i-1)) ) )
				continue;
			r = calc( newexp, -1 );
			ans = max(ans, r * sign);
	//		cout << "n:" << newexp << " r:" << r << endl;
		}
		for(int j=0; j<cs.length(); j++){
			newexp = exp.substr(0, i) + cs.at(j) + exp.substr(i);
			if( i != 0 && i != exp.length() && string::npos == cs.find( exp.at(i-1) ) && string::npos == cs.find( exp.at(i) ) ){
				r = calc( newexp, -1 );
				ans = max(ans, r * sign);
//				cout << "n:" << newexp << " r:" << r << endl;
			}
		}
		if( i != exp.length() ){
			newexp = exp.substr(0, i) + exp.substr(i+1);
			if( (i==0 || string::npos != cs.find(exp.at(i-1)) ) && ( i==exp.length()-1 || string::npos != cs.find(exp.at(i+1)) || exp.at(i+1) == '0' ) )
				continue;
			r = calc( newexp, -1 );
			ans = max(ans, r * sign);
		}
		
	}
	return ans * sign;
}

int main() {
	int N;
	calc("911+11",-1);
	string exp;
	while( cin >> N >> exp, N ){
		result r = faor( exp );
		int ans = r.value; 
		if( N % 2 ){
			ans = calc(exp);
		}else{
			ans = calc2(exp);
		}
		cout << ans << endl;
	}
}
