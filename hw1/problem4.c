#include <stdio.h>
#include <string.h>
double calculate(int i);
char cal[1000000];
char op[10000];
double n[10000];
double num=0;
int indexop=0;
int indexn=0;
int main(){
    while (scanf("%s", cal)!=EOF){
        int para=0;
        int ne=0;
        int l=strlen(cal);
        //printf("%s\n", cal);
        //printf("%c\n", cal[0]);
        int j=0;
        for (int i=0; i<l; i++){
            if (cal[i]=='*' || cal[i]=='/' || cal[i]=='+' || cal[i]=='-'){
                if (ne==1){
                    n[indexn]=num;
                    indexn+=1;
                    num=0;
                    ne=0;
                }
                //para=0;
                switch (cal[i]){
                    case '*':
                        calculate(0);
                        //printf("%c\n", '*');
                        break;
                    case '/':
                        calculate(0);
                        //printf("%c\n", '/');
                        break;
                    case '+':
                        calculate(1);
                        //printf("%c\n", '+');
                        break;
                    case '-':
                        calculate(1);
                        //printf("%c\n", '-');
                        break;
                }
                op[indexop]=cal[i];
                indexop+=1;
            }else if (cal[i]=='('){
                op[indexop]=cal[i];
                indexop+=1;
                //printf("%c\n", '(');
            }else if (cal[i]==')'){
                if (ne==1){
                    n[indexn]=num;
                    indexn+=1;
                    num=0;
                    ne=0;
                }
                calculate(1);
                indexop-=1;
                //para=1;
                //printf("%c\n", ')');
            }else{
                num*=10;
                num+=cal[i]-'0';
                ne=1;
                //printf("%.15f\n", num);
            }
        }
        //printf("%.15f\n", num);
        if (ne==1){
            n[indexn]=num;
            indexn+=1;
            num=0;
            ne=0;
        }
        calculate(1);
        
        //for (int i=0;i<10;i++){
            //printf("%.15f%c", n[i], op[i]);
        //}
        printf("%.15f\n", n[0]);
        num=0;
        indexop=0;
        indexn=0;
    }
    return 0;
}


double calculate(int i){
    if (indexn==1){
        return 0;
    }
    if (i==0){
        switch(op[indexop-1]){
            case '*':
                n[indexn-2] = n[indexn-2] * n[indexn-1];
                indexn-=1;
                indexop-=1;
                break;
            case '/':
                n[indexn-2] = n[indexn-2] / n[indexn-1];
                indexn-=1;
                indexop-=1;
                break;
        }
    }else if(i==1){
        while (indexop>0 && op[indexop-1]!='('){
            
            switch(op[indexop-1]){
                case '*':
                    n[indexn-2] = n[indexn-2] * n[indexn-1];
                    indexn-=1;
                    indexop-=1;
                    break;
                case '/':
                    n[indexn-2] = n[indexn-2] / n[indexn-1];
                    indexn-=1;
                    indexop-=1;
                    break;
                case '+':
                    n[indexn-2] = n[indexn-2] + n[indexn-1];
                    indexn-=1;
                    indexop-=1;
                    break;
                case '-':
                    n[indexn-2] = n[indexn-2] - n[indexn-1];
                    indexn-=1;
                    indexop-=1;
                    break;
            }
            //printf("%d", indexn);
        }
        
    }
    return 0;
}
