#include <iostream>
#include <set>
#include <vector>
#include <string>

using namespace std;

//数式格納用構造体(1つで1項に対応)
//numは数字のときに使用
//数式のときはexpに項数分格納される
//opeは次の項との演算に使う演算子
//ope='e'のときは次の項なし。()の終了
struct expr{
	set<int> num;
	char ope;
	vector<expr> exp;
	expr(){ ope = 0; }
};

//デバッグ用
void printexpr(expr e, int deep=0){
//	cout << "info: " << e.num.size() << " " << e.ope << " " << e.exp.size() << endl;
	if( e.num.empty() ){
		for(int i=0; i<e.exp.size(); i++){
			printexpr( e.exp[i], deep+1 );
		}
	}
	for(int i=0; i<deep; i++) cout << "  ";
	if( !e.num.empty() )
		cout << *( e.num.begin() );
	cout << e.ope << endl;
}

//計算して値を出す
set<int> calc(expr e){
//	cout << "calc" << endl;
//	printexpr(e,0);
	set<int> result;
	if( e.exp.size() == 0 ){
		result = e.num;
	}else if( e.exp.size() == 1 ){
		result = calc( e.exp[0] );
	}else if( e.exp.size() == 2 ){
		set<int> t[2];
		t[0] = calc( e.exp[0] );
		t[1] = calc( e.exp[1] );
		for(set<int>::iterator it0 = t[0].begin(); it0 != t[0].end(); it0++){
			for(set<int>::iterator it1 = t[1].begin(); it1 != t[1].end(); it1++){
				switch( e.exp[0].ope ){
				case '+':
					result.insert( *it0 + *it1 );
					break;
				case '-':
					result.insert( *it0 - *it1 );
					break;
				case '*':
					result.insert( *it0 * *it1 );
					break;
				case '/':
					if( *it1 != 0 )
						result.insert( *it0 / *it1 );
					break;
				}
			}
		}
	}else{
		//2項に分割して計算
		expr tmp, t;
		tmp.exp.push_back(t);
		tmp.exp.push_back(t);
		tmp.exp[1].ope = 'e';
		tmp.exp[1].exp = e.exp;
		for(int i=0; i<e.exp.size()-1; i++){
			if( !tmp.exp[0].exp.empty() )
				tmp.exp[0].exp.back().ope = tmp.exp[0].ope;
			tmp.exp[0].exp.push_back( e.exp[i] );
			tmp.exp[0].exp.back().ope = 'e';
			tmp.exp[0].ope = e.exp[i].ope;
			tmp.exp[1].exp.erase( tmp.exp[1].exp.begin() );
			set<int> rt = calc( tmp );
			for(set<int>::iterator it = rt.begin(); it != rt.end(); it++){
				result.insert( *it );
			}
		}
	}
//	cout << "result : " << result.size() << endl;
	return result;
}

//構文解析で用いる
expr *getexpr(expr *root, int deep){
	expr *pe = root;
	for(int k=0; k<=deep; k++){
		if( pe->exp.empty() || pe->exp.back().ope != 0 ){
			expr ex;
			pe->exp.push_back( ex );
		}
		pe = &( pe->exp.back() );
	}
	return pe;
}

void solve(string Str){
	struct expr exp;
	int tmp=0, deep=0;
	bool num_f=false;
	
	// 解析
	Str += "e";
	const char *str = Str.c_str();
	for(int i=0; str[i] != '\0'; i++){
		if( str[i] >= '0' && str[i] <= '9' ){
			tmp = tmp * 10 + ( str[i]-'0' );
			num_f = true;
			continue;
		}
		if( num_f ){
			getexpr(&exp,deep)->num.insert( tmp );
			tmp = 0;
			num_f = false;
		}
		if( str[i] == '(' ){
			deep++;
		}else if( str[i] == ')' ){
			getexpr(&exp,deep)->ope = 'e';
			deep--;
		}else{
			// 演算子登録
			getexpr(&exp,deep)->ope = str[i];
		}
	}

	printexpr( exp );

	//解く
	set<int> ans = calc( exp );
//	for(set<int>::iterator it = ans.begin(); it != ans.end(); it++){
//		cout << *it << " ";
//	}

	cout << ans.size() << endl;
}

int main(){
	string Str;
	while(1){
		cin >> Str;
		if( Str.at(0) == '#' )
			break;
		solve( Str );
	}
	return 0;
}
