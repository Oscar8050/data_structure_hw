#include <stdio.h>
#include <stdlib.h>

struct node{
    int priority;
    struct node *next;
};
typedef struct node Node;

#define XOR(a, b) (Node *)((intptr_t)(a)^(intptr_t)(b))

void insert(Node *list[], int cumulation[], int largest[]);
void delete(Node *list[], int cumulation[], int largest[]);
void increase(Node *list[], int cumulation[]);
void query(int largest[]);
void reverse();
void remov();

int N, Q;

int main(){
    
    
    scanf("%d %d", &N, &Q);
    //Node *head, *current;
    Node *list[N];
    int cumulation[N];
    int largest[N];
    for(int i=0;i<N;i++){
        list[i]=(Node *) malloc(sizeof(Node));
        scanf("%d", &list[i]->priority);
        list[i]->next=NULL;
        cumulation[i]=i+1;
        largest[i]=list[i]->priority;
    }
    while(Q--){
        int op;
        scanf("%d", &op);
        switch(op){
            case 1:
                insert(list, cumulation, largest);
                break;
            case 2:
                delete(list, cumulation, largest);
                break;
            case 3:
                increase(list, cumulation);
                break;
            case 4:
                query(largest);
                break;
            case 5:
                reverse();
                break;
            case 6:
                remov();
                break;
                
        }
        printf("main\n");
        for (int i=0;i<N;i++){
            printf("%d: ", largest[i]);
            printf("%d: ", cumulation[i]);
            Node *p;
            p=list[i];
            while(p!=NULL){
                printf("%d ", p->priority);
                p=p->next;
            }
            printf("\n");
        }
            
    }
    
    
    
    return 0;
}

void insert(Node *list[], int cumulation[], int largest[]){
    int p, k;
    Node *current, *previous;
    previous=NULL;
    int n;
    scanf("%d %d", &p, &k);
    Node *new;
    new=(Node *) malloc(sizeof(Node));
    new->priority=p;
    new->next=NULL;
    int L=0;
    int R=N;
    int index=(L+R)/2;
    int f,b;
    if(k==0){
        new->next=list[0];
        list[0]=new;
        if (new->priority>largest[0])
            largest[0]=new->priority;
        for (int i=0;i<N;i++)
            cumulation[i]+=1;
        return;
    }
    while(index!=0 && (cumulation[index]<k || cumulation[index-1]>k)){
        if(cumulation[index]<k)
            L=index;
        else
            R=index;
        index=(L+R)/2;
    }
    if(index<N-1 && cumulation[index]==cumulation[index+1] && cumulation[index]==k)
        index+=1;
    printf("index=%d\n", index);
    /*if index==0
        f=cumulation[0];
    else
        f=cumulation[index-1];
    b=cumulation[index];*/
    if(index!=0 && k==cumulation[index-1] && cumulation[index-1]-cumulation[index-2]<cumulation[index]-cumulation[index-1]){
        printf("1\n");
        if(list[index-1]==NULL){
            list[index-1]=new;
        }else{
            current=list[index-1];
            while(current->next!=NULL)
                current=current->next;
            current->next=new;
        }
        cumulation[index-1]+=1;
        if(new->priority>largest[index-1])
            largest[index-1]=new->priority;
    }else if(index!=0 && k==cumulation[index-1]){
        printf("2\n");
        if(list[index]!=NULL)
            new->next=list[index];
        list[index]=new;
        if(new->priority>largest[index])
            largest[index]=new->priority;
        //cumulation[index-1]+=1;
    }else if(k==cumulation[index]){
        printf("3\n");
        current=list[index];
        while(current->next!=NULL)
            current=current->next;
        current->next=new;
        if(new->priority>largest[index])
            largest[index]=new->priority;
    }else{
        printf("4\n");
        if(index!=0)
            n=cumulation[index-1]+1;
        else
            n=1;
        current=list[index];
        while(n!=k){
            current=current->next;
            n+=1;
        }
        new->next=current->next;
        current->next=new;
        if(new->priority>largest[index])
            largest[index]=new->priority;
    }
    while(index<N){
        cumulation[index]+=1;
        index+=1;
    }
    return;
}

void delete(Node *list[], int cumulation[], int largest[]){
    int k;
    int change;
    Node *current, *tmp;
    int n;
    scanf("%d", &k);
    int L=0;
    int R=N;
    int index=(L+R)/2;
    while(index!=0 && (cumulation[index]<k || cumulation[index-1]>=k)){
        if(cumulation[index]<k)
            L=index;
        else
            R=index;
        index=(L+R)/2;
    }
    //while(cumulation[index]==cumulation[index+1] && index<N-1 && cumulation[index]==k)
        //index+=1;
    while(list[index]==NULL)
        index-=1;
    printf("index=%d\n", index);
    if(k==1){
        tmp=list[index];
        list[index]=tmp->next;
        if(tmp->priority==largest[index]){
            current=list[index];
            if(current!=NULL)
                largest[index]=current->priority;
            else
                largest[index]=-32768;
            while(current!=NULL){
                if(current->priority>largest[index])
                    largest[index]=current->priority;
                current=current->next;
            }
        }
        free(tmp);
        //change=index;
        for(int i=index;i<N;i++)
            cumulation[i]-=1;
        return;
    }
    int a,af;
    if(index-1>=0)
        a=cumulation[index]-cumulation[index-1];
    else
        a=cumulation[index];
    if(index-2>=0)
        af=cumulation[index-1]-cumulation[index-2];
    else
        af=cumulation[index-1];
    /*if(index!=0 && k==cumulation[index-1]){
        if(af==1){
            tmp=list[index-1];
            list[index-1]=NULL;
        }else{
            printf("in\n");
            current=list[index-1];
            while(current->next->next!=NULL)
                current=current->next;
            tmp=current->next;
            current->next=NULL;
        }
        free(tmp);
        cumulation[index-1]-=1;
    }else */
    if(index!=0 && k==cumulation[index-1]+1){
        tmp=list[index];
        list[index]=tmp->next;
        //free(tmp);
        //change=index;
    }else if(k==cumulation[index]){
        /*if(cumulation[index]-cumulation[index-1]==1){
            tmp=list[index];
            list[index]=NULL;
        }else{*/
        current=list[index];
        while(current->next->next!=NULL)
            current=current->next;
        tmp=current->next;
        current->next=NULL;
        //}
        //free(tmp);
        //change=index;
    }else{
        if(index!=0)
            n=cumulation[index-1]+2;    //current要在前一個node才能處理
        else
            n=2;
        current=list[index];
        while(n!=k){
            current=current->next;
            n+=1;
        }
        tmp=current->next;
        current->next=tmp->next;
        //free(tmp);
    }
    if(tmp->priority==largest[index]){
        largest[index]=-32768;
        if(list[index]!=NULL){
            current=list[index];
            while(current!=NULL){
                if(current->priority>largest[index])
                    largest[index]=current->priority;
                current=current->next;
            }
        }
    }
    free(tmp);
    while(index<N){
        cumulation[index]-=1;
        index+=1;
    }
}

void increase(Node *list[], int cumulation[]){
    Node *current;
    int l, r, p;
    scanf("%d %d %d", &l, &r, &p);
    int L=0;
    int R=N;
    int index=(L+R)/2;
    while(index!=0 && (cumulation[index]<l || cumulation[index-1]>=l)){
        if(cumulation[index]<l)
            L=index;
        else
            R=index;
        index=(L+R)/2;
    }
    int n;
    if (index!=0)
        n=cumulation[index-1]+1;
    else
        n=1;
    current=list[index];
    while(n!=l){
        n+=1;
        current=current->next;
    }
    while(n!=r+1){
        while(current!=NULL && n!=r+1){
            current->priority+=p;
            current=current->next;
            n+=1;
        }
        index+=1;
        if(index==N || n==r+1)
            break;
        while(list[index]==NULL)
            index+=1;
        current=list[index];
    }
}
void query(int largest[]){
    int l, r;
    scanf("%d %d", &l, &r);
    int L=0;
    int R=N;
    int index=(L+R)/2;
    while(index!=0 && (cumulation[index]<l || cumulation[index-1]>=l)){
        if(cumulation[index]<l)
            L=index;
        else
            R=index;
        index=(L+R)/2;
    }
}
void reverse(){
    
}
void remov(){
    
}
