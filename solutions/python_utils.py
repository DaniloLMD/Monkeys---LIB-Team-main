#O inteiro do python ja é um big int!

#-------------- INPUT --------------#
inteiro, nome, double = input().split()
double = float(input())
inteiro = int(inteiro)

#o float do python é igual do c++ - tem apenas 64 bits. 
#Decimal é mais lento, mas é como um "big num" para numeros flutuantes
from decimal import Decimal, getcontext
PI_STR = (
"3.1415926535897932384626433832795028841971693993751058209749445923078164062862089"
"9862803482534211706798214808651328230664709384460955058223172535940812848111745028"
"410270193852110555964462294895493038196"
)
getcontext().prec = 25 #fixar precisao das operações. maior numero = + preciso e + lento

d = Decimal(input())
print(f"{d:.2f}")
eps = Decimal(10) ** -9 #Não fazer Decimal(10**-9), pois o de dentro vai ser o float normal.
PI = Decimal(PI_STR) #Não fazer PI = Decimal(acos-1) ou PI = Decimal(pi), pois os valores serão calculados em float antes

#-------------- OUTPUT --------------#
print("Em vez de quebrar linha, vai ter um espaço no final.", end=" ") #da pra usar end=" string completa"
print(f"string formatada! inteiro = {inteiro}")
print(f"Valor com 2 casas decimais: {double:.2f}")

#Desativando limite de digitos
import sys
sys.set_int_max_str_digits(0)  # 0 completely disables the limit


#-------------- FAST I/O --------------#
#Exemplo de input:
#N
#A1 A2 A3... An

import sys
data = sys.stdin.buffer.read().splitlines() # vai ler o input todo de uma vez e guardar cada linha em um indice de um vetor.
output = [] #vetor para guardar o output. Printar de uma vez é bem mais rapido que chamar varios prints.  
n = int(data[0])
for linha in data[1:]: #pula a primeira linha q era do valor N
    for valor in linha.split(): #valor vai ser um binario no formato b'1234'. 
        #Pode-se usar int(valor) para pegar o inteiro, ou val.decode() para transformar em string removendo a letra b e as aspas.
        output.append(valor.decode()) 
        # output.append(str(int(valor))) #mais lento, mas pode usar o int(valor) pra fazer calculos antes de voltar para string

sys.stdout.write("\n".join(output) + "\n") #imprime o output, separando os elementos por "\n" e printando "\n" no final.


#-------------- SET --------------#
s = set()
s.add(3)
s.add(5)          # insert            O(1) médio
for x in s:
    print(x) #3 5

5 in s            # find              O(1) médio  - True
s.remove(5)       # erase             O(1) médio  - erro se não existir
s.discard(99)     # erase             O(1) médio  - silencioso se não existir
len(s)            # size              O(1)
s.clear()

# operações de conjunto 
a, b = {1,2,3}, {2,3,4}
a | b   # união          {1,2,3,4}
a & b   # interseção     {2,3}
a - b   # diferença      {1}
a ^ b   # dif. simétrica {1,4}


#-------------- MAP / Dicionário --------------#
m = {}
m["pedro"] = 15.5      # insert (1) médio   
m["ana"] = "banana"
"pedro" in m           # find O(1) médio - True
m["pedro"]             # acesso O(1) médio - KeyError se não existir
m.get("zé")            # acesso, não dá erro
del m["ana"]           # erase O(1) médio. Da erro se não existir
m.pop("ana", None)     # erase sem erro

for chave, valor in m.items():   # iterar
    print(chave, valor)

freq = {}
for x in [1,2,3,1,3]:
    freq[x] = 0
for x in [1,2,3,1,3]:
    freq[x] += 1


#-------------- VECTOR / LIST --------------#
v = []
v.append(5)       # push_back         O(1) amortizado
v.pop()           # pop_back          O(1)
v[0]              # acesso            O(1)
v[-1]             # back()            O(1)
len(v)            # size              O(1)
v.pop(0)          # erase do início   O(n)  - cuidado
v.insert(2, 99)   # insert valor 99 no indice 2    O(n)
5 in v            # busca linear      O(n)  
v.reverse()       # O(n)
v = [0] * 100     # vector de tamanho 100
adj = [[] for _ in range(n)]   # lista de adjacência


#-------------- DEQUE --------------#
from collections import deque
d = deque()
d.append(1); d.appendleft(0)    # O(1) ambos
d.pop();     d.popleft()        # O(1) ambos

#-------------- TUPLA --------------#
tupla = (1, 2, 3) #imutável


#-------------- PRIORITY QUEUE (MIN) --------------#
import heapq
h = []
heapq.heappush(h, 5)      # push          O(log n)
heapq.heappush(h, 3)
h[0]                      # top           O(1): valor 3 (min)
heapq.heappop(h)          # pop           O(log n)
len(h)

lista = [1,2,3,-1]
heapq.heapify(lista)      # transforma lista em heap   O(n)

#Exemplo para dijkstra - tupla (peso, vertice). Ordena igual pair do C++.
q = []
heapq.heappush(q, (5,1))


#-------------- STRING --------------#
# Strings são imutáveis.
# Toda operação cria uma string nova - O(n), cuidado!

s = "Pedro"
s[0]          # 'P'      O(1)
s[1:3]        # "ed"     O(tamanho do intervalo R-L+1)
s + "!"       # cria nova string, O(n)
s.replace("e", "a") #troca as ocorrências de "e" por "a". Funciona para substrings.
"dro" in s    # busca de substring O(n + m), n = tamanho da string, m = tamanho da substring
s.upper(); s.lower() #maiusculo / minusculo

s.split() #Separa cada palavra, por espaços, em uma lista
s.split(sep=".") #Separa cada palavra, por ponto ".", em uma lista
linha = "sabino;leal,wevton;danilo"
print(linha.split(sep=";")) #Output: ['sabino', 'leal,wevton', 'danilo']

s.strip() #Remove todos os caracteres indesejados (padrão: espaço e \n) do inicio e do final da string
original = "!.,ab!,.12!!!...,,,!"
print(original.strip("!.,")) #Output: 'ab!,.12'
s.lstrip(); s.rstrip() #strip só pela esquerda / só pela direita


#Da pra converter uma lista em uma string
partes = [] #Para formar a string
for i in range(n):
    partes.append(str(i))
resultado = "".join(partes)      # O(total)

chars = list(s) #Para alterar a string
chars[0] = 'X'
s = "".join(chars)

#-------------- SORT --------------#
# sorted() e .sort() usam Timsort: O(n log n) e estável.
v = [3, 1, 2]
u = sorted(v)         # devolve nova lista, não altera v
v.sort()              # altera v
v.sort(reverse=True)  # decrescente

#Função propria de sort
alunos = [("Pedro", 15.5), ("Ana", 7.25), ("Bernardo", 15.5)]
alunos.sort(key=lambda a: a[1])              # pela nota
alunos.sort(key=lambda a: -a[1])             # nota decrescente
alunos.sort(key=lambda a: (-a[1], a[0]))     # nota desc, depois nome asc
alunos.sort(key=len)                         # qualquer função serve

#Similar ao C++
from functools import cmp_to_key
#Retornos da função de comparador:
#Negativo: A deve vir antes do B ; Zero: A e B são equivalentes ; Positivo: A deve vir depois do B
def cmp(a, b): #Ordena pelo menor v[0] e pelo maior v[1]
    if(a[0] == b[0]):
        return -1 if  a[1] >= b[1] else 1
    return -1 if a[0] <= b[0] else 1

v = [[3,4], [3,5], [1,2], [1,1]]
v.sort(key=cmp_to_key(cmp))
print(v) #Output: [[1, 2], [1, 1], [3, 5], [3, 4]]


#-------------- RANDOM --------------#
import random

random.randint(1, 10)      # inteiro entre 1 e 10, AMBOS inclusive
random.random()            # float em [0.0, 1.0)
random.uniform(1.5, 9.9)   # float em [1.5, 9.9]

v = [1,2,3,4]
random.shuffle(v) #embaralha
