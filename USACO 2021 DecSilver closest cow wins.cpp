#include <iostream>
#include <queue>
#include <set>
#include <vector>
#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int MAXN = 200000 + 10;
int p[MAXN], t[MAXN], f[MAXN]; 

struct node {
	int pos;
	int type;
	int index;
} ;
vector<node> data;
vector<long long> A;
bool cmp(node a, node b){
	return a.pos < b.pos;
}

long long sum_t(vector<int> &v){
	long long res = 0;
	for(int i = 0; i < v.size(); ++ i) res += t[v[i]];
	return res;	
}

int main(){	
	int K, n, m;
	scanf("%d %d %d", &K, &m, &n);
	for(int i = 0; i < K; ++ i){
		scanf("%d %d", &p[i], &t[i]);
		data.push_back((node){p[i], 0, i});
	}
	for(int i = 0; i < m; ++ i){
		scanf("%d", &f[i]);
		data.push_back((node){f[i], 1, i});
	}
	
	sort(data.begin(), data.end(), cmp);
	
	/*for(int i = 0; i < data.size(); ++ i){
		cout << data[i].type << ' ' << data[i].pos << endl; 
	}*/
	vector<int> Q;
	int index_old = -1;
	
	for(int i = 0; i < data.size(); ++ i)
		if(data[i].type){
			if(index_old == -1) A.push_back(sum_t(Q));
			if(index_old >= 0){
				int k = 0;
				long long ts = 0;
				long long tm = 0;
				int cowL = f[index_old];
				int cowR = data[i].pos;
				for(int j = 0; j < Q.size(); ++ j){
					int index = Q[j];
					long long myCow = 2 * p[index] - cowL;
					while(k < Q.size() && p[Q[k]] - myCow < cowR - p[Q[k]]){
						ts += t[Q[k]];
						++ k;
					}
					tm = max(ts, tm);
					ts -= t[Q[j]];
				}
				
				ts = sum_t(Q);
				
				A.push_back(ts - tm);
				A.push_back(tm);
			}
			
			Q.clear();
			index_old = data[i].index;
		}else{
			Q.push_back(data[i].index);
		}
	
	A.push_back(sum_t(Q));
	
	sort(A.begin(), A.end(), greater<long long>());
	long long ans = 0;
	//for(int i = 0; i < A.size(); ++ i) cout << "xx " << A[i] << endl;
	for(int i = 0; i < n && i < A.size(); ++ i){
		ans += A[i];
	}
	cout << ans << endl;
	return 0;
}
