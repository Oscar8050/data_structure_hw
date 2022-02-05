#include <stdio.h>
#include <stdlib.h>
#include "generator.h"

int cmp(const void *a, const void *b);
int lowbit(int x);
void init(int n);
void update(int x, int val);
int query(int x);
int bit[10000000];
int vertices[10000000][3];
int addleft[10000000];
int main(){
    generator.init();
    int t = generator.getT();
    while (t--){
        int n, *p, *q, *r;
        generator.getData(&n, &p, &q, &r);
        for(int i = 0; i < 10000000; i++)
            addleft[i]=0;
        //int vertices[n][3];
        //int ans = 0;
        int min=0;
        for (int i = 0; i < n; i++){
            if (r[i]<q[i]){
                int temp;
                temp=r[i];
                r[i]=q[i];
                q[i]=temp;
            }
            vertices[i][0]=p[i];
            vertices[i][1]=q[i];
            vertices[i][2]=r[i];
            if (vertices[i][0] < min){
                min = vertices[i][0];
            }
            if (vertices[i][1] < min){
                min = vertices[i][1];
            }
            if (vertices[i][2] < min){
                min = vertices[i][2];
            }
            //printf("%d\n", ans);
            //printf("%d %d %d\n", vertices[i][0], vertices[i][1], vertices[i][2]);
        }
        
        qsort(vertices, n, sizeof(int)*3, cmp);
        for (int i = 0; i < n; i++){
            vertices[i][0]-=min-1;
            vertices[i][1]-=min-1;
            vertices[i][2]-=min-1;
            //addleft[vertices[i][0]]+=1;
            addleft[vertices[i][1]]+=1;
            //addleft[vertices[i][2]]+=1;
            //printf("%d %d %d\n", vertices[i][0], vertices[i][1], vertices[i][2]);
        }
        
        init(n);
        long long int intersect=0;
        for (int i = 0; i < n; i++){
            update(vertices[i][1], -1);
            intersect += query(vertices[i][2]);
            //for (int i=0; i<25;i++){
                //printf("%lld ", bit[i]);
            //}
            //printf("\n");
            //printf("%d\n", intersect);
        }
        printf("%lld\n", intersect);
        
        //for (int i=0; i<25;i++){
            //printf("%lld ", bit[i]);
        //}
    }


    return 0;
}


int cmp(const void *a, const void *b){
    if (((int*)a)[0] != ((int*)b)[0]){
        return ((int*)a)[0] - ((int*)b)[0];
    }else{
        return ((int*)b)[2] - ((int*)a)[2];
    }
        
    
}

int lowbit(int x){
    return x&(-x);
}

void init(int n){
    for(int x = 1; x <=9999999; ++x){
        bit[x] = addleft[x];
        int y = x - lowbit(x);
        for (int i = x-1; i > y; i-=lowbit(i))
            bit[x] += bit[i];
     }
    
}

void update(int x, int val){
    for (int i = x; i <= 9999999; i += lowbit(i))
        bit[i] += val;
    
}

int query(int x){
    int sum = 0;
    for(int i = x; i > 0; i -= lowbit(i))
        sum += bit[i];
    return sum;
}
