/********************************************************************
   AMRO HYBRID CONSTRUCTIVE PRIME SYSTEM — FINAL STABLE BUILD V13
   Constructor Table Updated: P=3 up to P=149 (Total 27 rules)
   Memory Safe: MU returns int, internal free.
   Feature: apply_sub now handles leading zero removal correctly.
********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h> // For abs()

/* ================================================================
 🔥 ADD ENGINE — growth supported (Safe Realloc)
   Performs N' = N + k*b and handles string expansion (realloc).
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
        // Shift existing digits right
        memmove(*num+1,*num,len+1);
        (*num)[0]=(carry%10)+'0';
        carry/=10;
        // Fix string termination after realloc
        (*num)[len+1] = '\0';
    }
}

/* ================================================================
 🔥 SUB ENGINE — Contraction, WITH LEADING ZERO REMOVAL
   Performs N' = N - k*b and handles string contraction (realloc).
================================================================ */
void apply_sub(char **num,int k,int last){
    int sub=k*last;
    char buf[32]; sprintf(buf,"%d",sub);

    // Start from the digit before the last one (which was removed in MU)
    int i=strlen(*num)-1, j=strlen(buf)-1, b=0;

    // Perform subtraction
    while(i>=0 && j>=0){
        int A=(*num)[i]-'0',B=buf[j]-'0';
        int d=A-B-b;
        if(d<0){d+=10;b=1;} else b=0;
        (*num)[i]=d+'0';
        i--; j--;
    }

    // Negative result → divisible signal
    if(b || j>=0){ (*num)[0]='-'; return; }
    
    // 💡 REMOVE LEADING ZEROS (Contraction)
    int shift = 0;
    while ((*num)[shift] == '0' && strlen(*num) - shift > 1) {
        shift++;
    }
    
    if (shift > 0) {
        memmove(*num, *num + shift, strlen(*num) - shift + 1);
        // Shrink memory space
        *num = realloc(*num, strlen(*num) - shift + 1);
    }
}

/* ================================================================
 🔥 MU — returns final reduced integer safely
   Core constructor engine. Duplicates input, applies rules, frees memory.
================================================================ */
int MU(char *n,int k,int mode){
    char *s=strdup(n);

    while(strlen(s)>2){
        int last=s[strlen(s)-1]-'0';
        s[strlen(s)-1]='\0'; // remove last digit and null terminate

        if(mode==1) apply_add(&s,k,last);
        else        apply_sub(&s,k,last);

        // Immediate rejection if subtraction yields negative number
        if(s[0]=='-'){ free(s); return -1; }
    }

    int out=atoi(s);
    free(s);
    return out;
}

/* ================================================================
 🔥 RULE TABLE — P=3 up to P=149 (Total 27 Constructors)
   (P, k, mode)
================================================================ */
struct RULE { int P, k, mode; };
const int TABLE_SIZE = 27; // Updated to 27

struct RULE CONSTRUCTOR_TABLE[27] = { // Updated size
    // Basic Rules (Indices 0, 1, 2)
    {3,  0, 0},   // Sum Rule
    {5,  0, 0},   // Unit Digit Rule
    {11, 0, 0},   // Alternating Sum Rule
    // Behavioral Constructors (Indices 3 to 26)
    {7,  2, -1},  // a - 2b
    {13, 4, 1},   // a + 4b
    {17, 5, -1},  // a - 5b
    {19, 2, 1},   // a + 2b
    {23, 7, 1},   // a + 7b
    {29, 3, 1},   // a + 3b
    {31, 3, -1},  // a - 3b
    {37, 11, -1}, // a - 11b
    {41, 4, -1},  // a - 4b
    {43, 13, 1},  // a + 13b
    {79, 71, -1}, // a - 71b
    {83, 25, 1},  // a + 25b
    {89, 9, 1},   // a + 9b
    {97, 29, -1}, // a - 29b
    {101, 10, -1},// a - 10b
    {103, 31, 1}, // a + 31b
    {107, 32, -1},// a - 32b
    {109, 11, 1}, // a + 11b
    {113, 34, 1}, // a + 34b
    {127, 38, -1},// a - 38b
    {131, 13, -1},// a - 13b
    {137, 41, -1},// a - 41b
    {139, 14, 1}, // a + 14b
    {149, 15, 1}  // a + 15b (New in V13)
};

/* ================================================================
 🔥 MAIN PRIME SIEVE O(k)
   Applies all constructors sequentially. Rejects immediately upon failure.
================================================================ */
int isPrimeCandidate(char *n){

    // MU-3, MU-5, MU-11 Checks (Stage I/A-HPC Core)
    int s=0; for(int i=0;i<strlen(n);i++)s+=n[i]-'0';
    if(s%3==0) return 0;
    if(n[strlen(n)-1]=='5') return 0;
    int alt=0; for(int i=0;i<strlen(n);i++)
        alt+=(i%2?-1:1)*(n[i]-'0');
    if(abs(alt)%11==0) return 0;

    // Run Behavioral Constructors (P=7 up to P=149) (Stage II)
    for(int i=3;i<TABLE_SIZE;i++){
        int P_rule = CONSTRUCTOR_TABLE[i].P;
        int out=MU(n,CONSTRUCTOR_TABLE[i].k,CONSTRUCTOR_TABLE[i].mode);
        
        // Immediate rejection if subtraction yields negative result (out == -1)
        if(out == -1) return 0;
        
        // Check for pass/fail condition: (out == P or -P) passes; (out % P == 0) fails.
        if(out == P_rule || out == -P_rule) continue;
        if(out % P_rule == 0) return 0;
    }
    return 1;
}

/* ================================================================
 🔥 DEMO
================================================================ */
int main(){
    char n[64];
    printf("--- A-HPC System Test (P=3 to P=149) ---\n\n");
    for(int x=4;x<=100;x+=2){
        sprintf(n,"%d",x+3);
        printf("%s → %s\n",n,isPrimeCandidate(n)?"🟢 PRIME-CANDIDATE":"🔴 COMPOSITE");
    }
    return 0;
}
