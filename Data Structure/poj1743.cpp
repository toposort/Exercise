/**********************************************
给n个1..88的数字组成一个串S，要找出其中最长的“theme”，
theme是串S的一个子串，具体的定义是：
1.长度至少为5;
2.自身或者自身的变形在其他位置至少出现了一次
3.条件2中的两个子串不重叠。
变形的含义是对某个串，对他的每一位加上或减掉一个常数C，得到的新串就是原串的变形.
把相邻的两个数做差得到一个新串，然后就是在这个新串中找到一个最长的不重叠的出现两次以上的子串。
构造出height后，可以去二份答案+判定，
判定的时候，对连续的一段i..j若height[k]>=当前答案 ，
那么就把i..j归为一组，记录这组当中的sa值的最大和最小值，
也就是在原串中起点的位置，若位置之差大于当前答案，也就是这两个串不交叉，返回true。
循环完一遍height，如果没有合适的值，就返回false。
****************************************/

#include <iostream>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

const int maxn = 20001;
int num[maxn];
int sa[maxn], rank[maxn], height[maxn];
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

bool check(int k, int n){
    int minn = 1<<26, maxx = -1;
    for (int i = 2; i <= n; i++){
        if(height[i]>=k){
            minn = std::min(minn, sa[i]);
            maxx = std::max(maxx, sa[i]);
            if(maxx-minn>k) return true;
        }
        else minn = maxx = sa[i];
    }
    return false;
}

int main(){
    int n;
    while(~scanf("%d", &n)){
        if(n==0) break;
        for(int i = 0; i < n; i++){
            scanf("%d", &num[i]);
        }
        if(n<10){
            puts("0");
            continue;
        }
        for(int i = 0; i < n-1; i++){
            num[i] = num[i+1]-num[i]+90;
        }
        num[n]=0;
        da(num, n+1, 200);
        calHeight(num, n);
        int l = 0, r = 1+(n>>1), mid;
        while(l+1<r){
            mid = (l+r)>>1;
            if(check(mid, n)) l = mid;
            else r = mid;
        }
        if(l<4) puts("0");
        else printf("%d\n", l+1);
    }
    return 0;
}

