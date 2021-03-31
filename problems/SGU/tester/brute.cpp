#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

int main()
{
   //freopen("input.txt","r",stdin);
    int k;
    scanf("%d",&k);
    int p[100];
    int f[512];
    int pos[512];
    while(k--)
    {
        memset(pos,0,sizeof(pos));
        int m,n;
        scanf("%d%d",&n,&m);
        for(int i=0;i<m;i++)
            scanf("%d",&p[i]);
        p[m++] = 1;
        sort(p,p+m);
        int t = 0;
        for(int i=0;i<m;i++)
            if(p[i]!=p[i+1] || i == m-1)p[t++] = p[i];
        m = t;
        f[1] = 0;
        int l2 = 2,l1 = -1;
        int x = 0;
        while(l1 == -1)
        {
            f[l2] = 1;
            for(int i=0;i<m && l2-p[i] > 0 && f[l2];i++) f[l2] &= f[l2-p[i]];
            f[l2] = !f[l2];
            if(pos[x]) l1 = pos[x];
            else
            {
                pos[x] = l2;
                x = (x<<1) & 0x1ff | f[l2];
                l2++;
            }
        }
        int ans;
        if(n<=l1) ans = f[n];
        else ans = f[(n-l1)%(l2-l1)+l1];
        if(ans)printf("FIRST PLAYER MUST WIN\n");
        else printf("SECOND PLAYER MUST WIN\n");
    }
    return 0;
}
