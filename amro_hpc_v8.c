/********************************************************************
   AMRO HYBRID CONSTRUCTIVE PRIME SYSTEM — FINAL STABLE BUILD V6
   No memory leaks — MU returns int — Fully scalable O(k)
********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* ================================================================
 🔥 ADD ENGINE — growth supported
================================================================ */
void apply_add(char **num,int k,int last){
    int carry=k*last,i=strlen(*num)-1;

    while(i>=0 && carry>0){
        int d=(*num)[i]-'0'+carry;
        (*num)[i]=(d%10)+'0';
        carry=d/10;
        i--;
    }
    while(carry>0){
        int len=strlen(*num);
        *num=realloc(*num,len+2);
        memmove(*num+1,*num,len+1);
        (*num)[0]=(carry%10)+'0';
        carry/=10;
    }
}

/* ================================================================
 🔥 SUB ENGINE — contraction only (no realloc)
================================================================ */
void apply_sub(char **num,int k,int last){
    int sub=k*last;
    char buf[32]; sprintf(buf,"%d",sub);

    int i=strlen(*num)-1,j=strlen(buf)-1,b=0;

    while(i>=0 && j>=0){
        int A=(*num)[i]-'0',B=buf[j]-'0';
        int d=A-B-b;
        if(d<0){d+=10;b=1;} else b=0;
        (*num)[i]=d+'0';
        i--; j--;
    }

    // negative result → divisible
    if(b || j>=0){ (*num)[0]='-'; }
}

/* ================================================================
 🔥 MU — returns final reduced integer safely
================================================================ */
int MU(char *n,int k,int mode){
    char *s=strdup(n);

    while(strlen(s)>2){
        int last=s[strlen(s)-1]-'0';
        s[strlen(s)-1]='\0';

        if(mode==1) apply_add(&s,k,last);
        else        apply_sub(&s,k,last);

        if(s[0]=='-'){ free(s); return -1; } // divisible
    }

    int out=atoi(s);
    free(s);
    return out;
}

/* ================================================================
 🔥 RULE TABLE — 13 Constructors (stage-II core)
================================================================ */
struct RULE{int P,k,mode;};
struct RULE T[13]={
 {3,0,0},{5,0,0},{11,0,0},
 {7,2,-1},{13,4,1},{17,5,-1},{19,2,1},
 {23,7,1},{29,3,1},{31,3,-1},{37,11,-1},
 {41,4,-1},{43,13,1}
};

/* ================================================================
 🔥 MAIN PRIME SIEVE O(k)
================================================================ */
int isPrimeCandidate(char *n){

    int s=0; for(int i=0;i<strlen(n);i++)s+=n[i]-'0';
    if(s%3==0) return 0;

    if(n[strlen(n)-1]=='5') return 0;

    int alt=0; for(int i=0;i<strlen(n);i++)
        alt+=(i%2?-1:1)*(n[i]-'0');
    if(alt%11==0) return 0;

    for(int i=3;i<13;i++){
        int out=MU(n,T[i].k,T[i].mode);
        if(out==T[i].P||out==-T[i].P) continue;
        if(out%T[i].P==0) return 0;
    }
    return 1;
}

/* ================================================================
 🔥 DEMO
================================================================ */
int main(){
    char n[64];
    for(int x=4;x<=100;x+=2){
        sprintf(n,"%d",x+3);
        printf("%s → %s\n",n,isPrimeCandidate(n)?"🟢 PRIME":"🔴 COMPOSITE");
    }
}
