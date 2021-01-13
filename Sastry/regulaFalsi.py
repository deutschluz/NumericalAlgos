
def regulafalsi(f,a,b,iters):
    def chord(f,a,b):
        return (a*f(b) - b*f(a))/(f(b) - f(a))
    count=0
    while count< iters:
        count += 1
        x1=chord(f,a,b)
        if f(x1)*f(a) < 0:
           b=x1
        else:
            a=x1
    return x1

def f(x): return x**3 +x**2 -1
print("root is {}".format(regulafalsi(f,2,3,100)))
