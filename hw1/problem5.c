#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
struct node{
    int data;
    struct node *link;
};
typedef struct node Node;
#define XOR(a, b) (Node *)((intptr_t)(a)^(intptr_t)(b))
void enter(Node **F, int add, Node **B);
void leave(Node **F,Node **B);
void migrate(Node **OF, Node **OB, Node **MF, Node **MB);
int main(){
    int rail_n, n;
    scanf("%d %d", &rail_n, &n);
    Node *rf[rail_n];
    Node *rb[rail_n];
    
    for (int i=0; i<rail_n; i++){
        rf[i]=NULL;
        rb[i]=NULL;
    }
    
    //printf("%p\n",r[0]);
    //enter(r[0],1);
    
    for (int i=0;i<n;i++){
        //printf("%d", n);
        char com[200];
        int n, lab;
        scanf("%s", com);
        if (com[0] == 'l'){
            scanf("%d", &n);
            if (rf[n]!=NULL){
                leave(&rf[n],&rb[n]);
            }
            //printf("%s\n", "leave");
            //printf("%d\n", n);
        }else if (com[0] == 'e'){
            scanf("%d %d", &n, &lab);
            enter(&rf[n], lab, &rb[n]);
            //printf("%p\n", &rb[n]);
            //printf("%s\n", "enter");
           // printf("%d %d\n", n, lab);
        }else if (com[0] == 'm'){
            scanf("%d %d", &n, &lab);
            //printf("%d", 3);
            if (rb[n]!=NULL){
                migrate(&rf[n], &rb[n], &rf[lab], &rb[lab]);
                //printf("%s\n", "migrate");
                //printf("%d %d\n", n, lab);
            }
            //r[n]=NULL;
        }else{
            printf("%s", "wrong input");
        }
    }
    Node *current, *previous, *next;
    
    for (int i=0; i<rail_n; i++){
        //printf("%d\n", i);
        current=rf[i];
        previous=NULL;
        /*if (current!=NULL){
            printf("%d ", current->data);
            previous=current;
            if (current->next!=NULL){
                current=current->next;
            }else{
                current=current->prev;
            }
        }*/
        while (current!=NULL){
            printf("%d ", current->data);
            next=XOR(previous, current->link);
            previous=current;
            current=next;
            
        }
        printf("\n");
    }
    /*for (int i=0; i<rail_n; i++){
        current=rb[i];
        previous=NULL;
        while (current!=NULL){
            printf("%d ", current->data);
            next=XOR(previous, current->link);
            previous=current;
            current=next;
        }
        printf("\n");
    }*/
    /*for (int i=0; i<rail_n; i++){
        printf("%d\n", i);
        current=rb[i];
        while (current!=NULL){
            printf("%d ", current->data);
            current=current->prev;
        }
        printf("\n");
         
        current=rb[i];
        if (current!=NULL){
            printf("%d ", current->data);
            previous=current;
            if (current->next!=NULL){
                current=current->next;
            }else{
                current=current->prev;
            }
        }
        while (current!=NULL){
            printf("%d ", current->data);
            if (current->next!=previous){
                previous=current;
                current=current->next;
            }else{
                previous=current;
                current=current->prev;
            }
            
        }
        printf("\n");
    }
    */
    
    return 0;
}

void enter(Node **F, int add, Node **B){
    if (*F==NULL){
        *F=(Node *) malloc(sizeof(Node));
        Node *current;
        current=*F;
        current->data = add;
        current->link = NULL;
        *B=*F;
        //printf("%s\n", "okay");
    }else{
        Node *current, *previous, *next;
        previous=*B;
        current=(Node *) malloc(sizeof(Node));
        current->data=add;
        previous->link=XOR(previous->link, current);
        //printf("%p\n", previous->link);
        current->link=XOR(previous,NULL);
        *B=current;
    }
    //printf("%p\n", N);
    return;
}

void leave(Node **F,Node **B){
    Node *current, *tmp, *prev;
    current = *B;
    if (current->link==NULL){
        *B=NULL;
        *F=NULL;
        free(current);
    }else{
        tmp=current;
        prev=current->link;
        prev->link=XOR(prev->link, current);
        free(tmp);
        *B=prev;
        
    }
    return;
}

void migrate(Node **OF, Node **OB, Node **MF, Node **MB){
    //printf("%d", 2);
    if (*MB==NULL){
        *MF=*OB;
        *MB=*OF;
        //printf("%p", *MB);
        /*Node *mb, *ob;
        mb=*MB;
        ob=*OB;
        if (ob->prev == NULL){
            *OB=NULL;
            return;
        }
        ob=ob->prev;
        mb->next=NULL;
        mb->prev=NULL;
        ob->next=NULL;
        *MB=mb;
        printf("%p", *MB);
        *OB=ob;*/
        *OF=NULL;
        *OB=NULL;
        return;
    }
    Node *current, *previous, *mcurrent;
    current = *OB;
    mcurrent = *MB;
    mcurrent->link=XOR(mcurrent->link, current);
    current->link=XOR(current->link, mcurrent);
    *MB=*OF;
    *OF=NULL;
    *OB=NULL;
    
    /*if (mcurrent->link==NULL && current->prev==NULL){
        mcurrent->link=current;
        current->prev=mcurrent;
    }else if(mcurrent->next==NULL && current->next==NULL){
        mcurrent->next=current;
        current->next=mcurrent;
    }else if(mcurrent->prev==NULL && current->next==NULL){
        mcurrent->prev=current;
        current->next=mcurrent;
    }else{
        mcurrent->prev=current;
        current->prev=mcurrent;
    }
    *MB=*OF;
    *OF=NULL;
    *OB=NULL;*/
    return;
}
