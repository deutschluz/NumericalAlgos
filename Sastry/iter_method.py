from pdb import set_trace
from math import fabs,sqrt,cos
# Fixed Point Root finding method
# PREAlgorithm Computation:  given a function in the form f(x)=0,
#  transform the equation into one that looks like x=g(x) where g and f
# are obviously related algebraically

# for example:
def f(x):
    return x**3 + x**2 -1

def f1(x): return (cos(x) -2*x+ 3)

def g1(x): return (cos(x)+3)/2
# then choose either x**2 or x**3 to be on the other side and isolate the x;
#and g(x) is the right-hand side
def g(x):
    return 1/(sqrt(1 + x))

def iter_method(func, x0, eps,iters):
    iters = iters or 0;
    xnext=func(x0)
    if fabs(xnext - x0) < eps:
        return xnext
    elif iters > 30:
        return xnext
    else:
        return iter_method(func,xnext,eps,iters+1)

#Aitken's Delta Process adds some precomputation to the general iterative method
# prev_x, curr_x, next_x := xi-1,xi,xi+1 , respectively.
def Delta(next_x,curr_x): return next_x - curr_x

def Delta2(next_x,curr_x,prev_x): return next_x -2*curr_x + prev_x

def Aitken_Aux(prev_x,curr_x,next_x,eps,iters):
    d1=Delta(next_x,curr_x)
    d2=Delta(curr_x,prev_x)
    #now perform this transformation: curr=>prev; next=>curr
    # and next => curr_x - (d1**2)/(d1-d2) 
    prev_x=curr_x; curr_x=next_x
    next_x= curr_x - (d1*d1)/(d1-d2)
    if fabs(next_x - curr_x)<eps:
        return next_x
    elif iters > 50:
        return next_x
    else:
        return Aitken_Aux(prev_x,curr_x,next_x,eps,iters+1)
      
def AitkenDelta(func,x0,eps,iters):
    prev_x=x0;
    curr_x=func(x0)
    next_x=func(curr_x)
    return Aitken_Aux(prev_x,curr_x,next_x,eps,iters)

def main():
   # set_trace()
    print("the root of x^3 + x^2 -1 in 0,1 is: {}".format(iter_method(g,0.75,1e-10,0)))
    print("Using Aitkens Method;\n")
    print("the root of cos -2x +3  in 0,1 is: {}".format(AitkenDelta(g,0.75,1e-10,0)))

    
main()
