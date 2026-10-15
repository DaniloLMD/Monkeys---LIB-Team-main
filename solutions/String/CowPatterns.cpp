
// https://vjudge.net/problem/POJ-3167
#include <stdio.h>
#define get_bit(x,i) ((x)&(1ll<<(i)))
#define MAX 100010

int a[MAX],b[MAX],p[MAX<<1];
int init[30];
int ans[MAX];
int n,k,s;
 
int get_char(int i){
    return (i < k ? b[i] : a[i-(k+1)]);
}
// a comparacao eh sempre entre um caracter do pattern (o i) e outro caracter, pode ser o do pattern ou o do texto
int cmp(int i,int j){
    int c;
    int at_c = b[i]; // caracter atual do pattern
    int l = j-i; // temos que de l ate j-1 temos match com 0 ate i-1, ai vamos ver agora o i com o j
    int mate = l+init[at_c]; // estamos analisando o caracter at_c, vamos ver o match da primeira aparicao desse caracter no pattern (init[at_c]) com a primeira aparicao no texto (l + init[at_c])
    if(i == k || j == k) return 0; // o i ou o j eh o caracter "#" (caracter que nao tem match com nenhum)
    if(init[at_c] < i) return get_char(j) == get_char(mate); // o caracter at_c nao apareceu pela primeira vez, agora eu so preciso ver se o j bate com a primeira vez que esse caracter aparece
    for(c=0; c<s; c++){
        // c always != at_c
        // se o caracter c ja apareceu e (o caracter atual eh igual a outro caracter do pattern || um caracter que eh menor que o atual apareceu, mas o valor dele eh maior que o atual no texto )
        if(init[c] < i && (get_char(l+init[c]) == get_char(j) || (c < at_c) != (get_char(l+init[c]) < get_char(j)))) return 0;
    }
    return 1;
}
 
void test(){
    /*
        A ideia eh fazer um KMP, mas manter uma especie de tabela dos valores pra cada valor do pattern para o valor real dele, ai inicialmente todos os valores nao
    tem uma relacao com um valor real, dai quando demos match dele com um valor estabelecemos uma relacao de equivalencia entre o pattern e o valor real dele no texto.
    Dai fazemos o KMP e pra cada caracter guardamos a primeira vez que ele aparece, quando tentamos dar match de um valor que aparece pela primeira vez, temos que ver
    se dar match desse valor atrapalha outros matchs, ou seja, esse valor no texto ja foi mapeado pra outro caracter do pattern ou um caracter menor do pattern ta mapeado
    um valor maior que o atual do texto ou o mesmo raciocinio pra caracter maior e valor no texto menor, se ocorrer erro, entao nao tem como dar match. Dai se o match
    da certo entao vc pode aumentar o valor do KMP.
    */
    int i,j,aux;
    int m = 0;
    scanf("%d %d %d", &n, &k, &s);
    for(i=0; i<s; i++) init[i] = k; // coloco quando cada caracter aparece a primeira vez no pattern, ai setto o infinito
    for(i=0; i<n; i++){
        scanf("%d", a+i);
        a[i]--;
    }
    for(i=0; i<k; i++){
        scanf("%d", b+i);
        b[i]--;
        if(init[b[i]] == k) init[b[i]] = i;
    }
    p[0] = 0;
    for(i=1; i<k+1+n; i++){
        j = p[i-1];
        while(j != 0 && !cmp(j,i)) j = p[j-1];
        if(cmp(j,i)) j++;
        p[i] = j;
    }
    for(i=k+1; i<k+1+n; i++) if(p[i] == k) ans[m++] = i-2*k + 1; // tirar da reindexacao e tirar que eu quero a pos init
    printf("%d\n",m);
    for(i=0; i<m; i++) {
        printf("%d\n",ans[i]);
    }
}
 
int main(){
    int ttt_ = 1;
    while(ttt_--) test();
    return 0;
}