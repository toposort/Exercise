#include <stdio.h>
#include <string.h>

const int maxn = 200011;
int len, len1;
int wa[maxn], wb[maxn], wv[maxn], wd[maxn], sa[maxn];
int lcp[maxn], r[maxn], rank[maxn], height[maxn];

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
    int k;
    char str1[maxn], str2[maxn];
    while(~scanf("%d", &k)){
        if(k==0) break;
        scanf("%s%s",str1, str2);
        len1 = strlen(str1);
        len = strlen(str2);
        for(int i = 0; i < len1; i++){
            r[i] = str1[i];
        }
        r[len1] = '$';
        for(int i = 0; i < len; i++){
            r[i+len1+1] = str2[i];
        }
        len += len1+1;
        r[len] = 0;
        da(r, len+1, 150);
        calHeight(r, len);
        long long res = 0, sum;
        int head, tail;
        for(int i = 1; i <= len; i++){
            if(height[i] < k){
                sum = 0;
                head = tail = maxn;
            }
            else{
                for(int j = head; j < tail; j++){
                    if(lcp[j] > height[i]){
                        sum -= lcp[j]-height[i];
                        lcp[j] = height[i];
                    }
                    else break;
                }
                if(sa[i-1] > len1){
                    lcp[--head] = height[i];
                    sum += lcp[head]-k+1;
                }
                if(sa[i] < len1) res += sum;
            }
        }
        for(int i = 1; i <= len; i++){
            if(height[i] < k){
                sum = 0;
                head = tail = maxn;
            }
            else{
                for(int j = head; j < tail; j++){
                    if(lcp[j] > height[i]){
                        sum -= lcp[j]-height[i];
                        lcp[j] = height[i];
                    }
                    else break;
                }
                if(sa[i-1] < len1){
                    lcp[--head] = height[i];
                    sum += lcp[head]-k+1;
                }
                if(sa[i] > len1) res += sum;
            }
        }
        printf("%I64d\n", res);
    }
}

