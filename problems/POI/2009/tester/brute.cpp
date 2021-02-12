#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

const int maxn = 1e5+10;

int n, s, k;
ll qtd[maxn][30], rest[maxn][30], resp;

vector<int> graph[maxn];

void dfs(int u, int f)
{
	for(int v: graph[u])
	{
		if(v == f) continue;

		dfs(v, u);

		for(int i = 0 ; i < k ; ++i) qtd[u][i+1] += qtd[v][i];
		
		for(int i = k ; i >= 1 ; --i) rest[u][i-1] += rest[v][i];
	}

	qtd[u][0]++;

	ll add = qtd[u][k]/s;

	if(qtd[u][k]%s > 0)	add++;

	resp += add;
		
	rest[u][k] += add*s;
		
	for(int i = 0 ; i <= k ; ++i) 
	{
		ll dif = min(qtd[u][i], rest[u][i]);

		qtd[u][i] -= dif; rest[u][i] -= dif;
	}

	for(int i = 0 ; i < k ; ++i) 
	{
		ll dif = min(qtd[u][i], rest[u][i+1]);

		qtd[u][i] -= dif; rest[u][i+1] -= dif;
	}

}

int main()
{
	cin >> n >> s >> k;

	for(int i = 1 ; i < n ; ++i)
	{
		int u, v;
		cin >> u >> v;

		graph[v].push_back(u);
		graph[u].push_back(v);
	}

	dfs(1, 0);

	ll r = 0LL;

	for(int i = k ; i >= 0 ; --i)
	{
		r += rest[1][i];
		
		if(r < qtd[1][i])
		{
			ll add = (qtd[1][i] - r)/s;

			if((qtd[1][i] - r)%s) add++;

			resp += add;

			r += add*s;
		}

		r -= qtd[1][i];
	}

	cout << resp << "\n";
}
