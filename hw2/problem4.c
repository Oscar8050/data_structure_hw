#include <stdio.h>
void check(int i, int key[], int left[], int right[], int t[], int lb, int rb);
int main(){
    int n;
    scanf("%d", &n);
    int key[n], left[n], right[n], t[n];
    for (int i=0; i<n; i++){
        scanf("%d %d %d", &key[i], &left[i], &right[i]);
    }
    //printf("%d\n",1);
    check(0, key, left, right, t, 0, 2147483647);
    t[0]=1;
    int count=0;
    for (int i=0;i<n;i++){
        if (t[i]==1){
            count+=1;
        }
        //printf("%d ",t[i]);
    }
    printf("%d", count);
    return 0;
}

void check(int i, int key[], int left[], int right[], int t[], int lb, int rb){
    int lrb=rb, rlb=lb;
    //printf("%d\n",2);
    if (left[i]!=-1){
        if (key[left[i]-1]<key[i]&&key[left[i]-1]<rb&&key[left[i]-1]>lb){
            t[left[i]-1]=1;
        }else{
            t[left[i]-1]=-1;
            //printf("%d\n", t[left[i]-1]);
        }
        //printf("%d\n",i);
        if (key[i]<rb){
            lrb=key[i];
        }
        check(left[i]-1, key, left, right, t, lb, lrb);
    }//else{
        //printf("%d\n",3);
        //return;
    //}
    //c=co;
    if (right[i]!=-1){
        //printf("%d %d\n", c, i);
        
            //printf("%d", right[i]);
            //printf("%d", t[right[i]-1]);
        if (key[right[i]-1]>key[i]&&key[right[i]-1]<rb&&key[right[i]-1]>lb){
            t[right[i]-1]=1;
        }else{
            t[right[i]-1]=-1;
        }
        //printf("%d\n", 123);
        if (key[i]>lb){
            rlb=key[i];
        }
        check(right[i]-1, key, left, right, t, rlb, rb);
    }//else{
        //return;
    //}
    return;
}
