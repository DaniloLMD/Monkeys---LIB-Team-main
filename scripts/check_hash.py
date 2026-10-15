import sys, hashlib

def h(s): return hashlib.sha256("".join(s.split()).encode()).hexdigest()[:4]

src = open(sys.argv[1]).read().splitlines()
got = [h(l) for l in src] + [h("".join(src))]
want = [x.split()[-1] for x in open(sys.argv[1] + ".hash").read().splitlines()]
print("erros:", [i for i, (a, b) in enumerate(zip(got, want), 1) if a != b])
print(len(src), "linhas, esperado", len(want) - 1)
