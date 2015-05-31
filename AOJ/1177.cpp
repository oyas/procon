#include <iostream>
#include <cmath>

using namespace std;

int main(){
	int len, x1, y1, x2, y2;
	while(cin>>len>>x1>>y1>>x2>>y2, len|x1|y1|x2|y2){
		double ans=0.0;
		// 扱いやすいように回転させる
		if( x1<0 && x2<0 ){
			int tmp = x1 * -1;
			x1 = x2 * -1;
			x2 = tmp;
		}
		if( y1<0 && y2<0 ){
			int tmp = y1 * -1;
			y1 = y2 * -1;
			y2 = tmp;
		}
		// 3パターンに分ける
		if( x1 > 0 && y1 > 0 ){
			int h2 = len*len-x1*x1, w2 = len*len-y1*y1;
			ans = 1.5 * len * M_PI;
			if( x1*x1 + y1*y1 > len*len ){
				ans += 0.5 * len * M_PI;
			}else{
				//左
				if( h2 <= y2*y2 ){
					ans += (double)len * (M_PI_2 - acos( (double)x1*x1/((double)len*len) ));
				}else{
					double r1 = atan( (double)y2*y2/((double)x1*x1) );
					ans += (double)len * (M_PI_2 - r1);
					if( x1*x1+y2*y2+(x2-x1)*(x2-x1) <= len*len ){
						ans += ((double)len-sqrt(x1*x1+y2*y2)) * r1;
					}else{
					}
				}
				//右
				if( h2 <= y2*y2 ){
					ans += (double)len * (M_PI_2 - acos( (double)x1*x1/((double)len*len) ));
				}else( x1*x1+y2*y2+(x2-x1)*(x2-x1) <= len*len ){
					double r1 = atan( (double)y2*y2/((double)x1*x1) );
					ans += (double)len * (M_PI_2 - r1);
					ans += ((double)len-sqrt(x1*x1+y2*y2)) * r1;
				}else{
				}
			}
		}else if( x1 < 0 ){
		}else if( y1 < 0 ){
		}
		cout << ans << endl;
	}
	return 0;
}
