#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int maxn = 100011<<1;
char num[maxn];
int sa[maxn], rank[maxn], height[maxn], r[maxn];
int wa[maxn], wb[maxn], wv[maxn], wd[maxn];

int cmp(int *r, int a, int b, int l){
    return r[a] == r[b] && r[a+l] == r[b+l];
}

void da(int *r, int n, int m){
    int i, j, p, *x=wa, *y=wb, *t;
    for(i = 0; i < m; i++) wd[i] = 0;
    for(i = 0; i < n; i++) wd[x[i] = r[i]]++;
    for(i = 1; i < m; i++) wd[i] += wd[i-1];
    for(i = n-1; i >= 0; i--) sa[--wd[x[i]]] = i;
    for(j = 1, p = 1; p < n; j *= 2, m = p){
        for(p = 0, i = n-j; i < n; i++) y[p++] = i;
        for(i = 0; i < n; i++) if(sa[i] >= j) y[p++] = sa[i]-j;
        for(i = 0; i < n; i++) wv[i] = x[y[i]];
        for(i = 0; i < m; i++) wd[i] = 0;
        for(i = 0; i < n; i++) wd[wv[i]]++;
        for(i = 1; i < m; i++) wd[i] += wd[i-1];
        for(i = n-1; i >= 0; i --) sa[--wd[wv[i]]] = y[i];
        for(t = x, x = y, y = t, p = 1, x[sa[0]] = 0, i = 1; i < n; i++){
            x[sa[i]] = cmp(y, sa[i-1], sa[i], j) ? p-1: p++;
        }
    }
}

void calHeight(int *r, int n){
    int i, j, k = 0;
    for(i = 1; i <= n; i++) rank[sa[i]] = i;
    for(i = 0; i < n; height[rank[i++]] = k){
        for(k ? k-- : 0, j = sa[rank[i]-1]; r[i+k] == r[j+k]; k++);
    }
}

int main(){
    gets(num);
    int len = strlen(num);
    num[len] = 1;
    gets(num+len+1);
    int len1 = strlen(num);
    for(int i = 0; i < len1; i++){
        r[i] = num[i];
    }
    da(r, len1+1, 256);
    calHeight(r, len1);
    int maxx = -1;
    for(int i = 2; i <= len1; i++){
        if((sa[i-1]>len&&sa[i]<len) || (sa[i-1]<len&&sa[i]>len)){
            maxx = std::max(maxx, height[i]);
        }
    }
    printf("%d\n", maxx);
    return 0;
}

