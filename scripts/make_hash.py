import sys, hashlib

def h(s): return hashlib.sha256("".join(s.split()).encode()).hexdigest()[:4]

lines = open(sys.argv[1]).read().splitlines()
out = [f"{i:03d} {h(l)}" for i, l in enumerate(lines, 1)] + ["ALL " + h("".join(lines))]
open(sys.argv[1] + ".hash", "w").write("\n".join(out) + "\n")
