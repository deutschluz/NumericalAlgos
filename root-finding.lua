-- bisect.lua
-- bisection method for solving non-linear equations



function bisect(f,a,b,fa,fb)
   local delta=1e-10	-- tolerance
   local c=(a+b)/2
   if c==a or c==b or math.abs(a-b)<delta then
      return c,b-a end
   n=n+1
   local fc=f(c)
   if fa*fc<0 then
      return bisect(f,a,c,fa,fc)
   else
      return bisect(f,c,b,fc,fb)
   end
end

-- find root of f in the inverval [a,b]. needs f(a)*f(b)<0
function solve(f,a,b)
 n=0
 local z,e=bisect(f,a,b,f(a),f(b))
 io.write(string.format("after %d steps, root is %.17g with error %.1e, f=%.1e\n",n,z,e,f(z)))
end

-- our function
function f(x)
 return x*x*x-x-1
end

-- find zero in [1,2]
solve(f,1,2)

--fixed-point transform
function FixedPointTransform(func, guess1)
   function closeEnough(v1,v2)
      local eps=0.00001  --tolerance 
      return math.abs(v1-v2)<eps
   end
   function try(guess)
      local next=func(guess)
      if closeEnough(guess,next) then
         return next
      else return try(next)
      end
   end
   return try(guess1)
end

print("the fixed point of cos starting at 1 is ",
      FixedPointTransform(math.cos,1))

function f(x)
   return math.sin(x) + math.cos(x)
end
print("the fixed point of sin x + cos x starting at 1 is ",
     FixedPointTransform(f,1))

--Exercise 13, pg. 305, Ch.5.1, Func. Anal.
--f1 and g are related such that the fixed point of g is the fixed point
-- of f1
function f1(x)
   return x*x*x + x - 1
end

function g(x)
   return 1/(1+x*x)
end

   
--print("the fixed point of f(x)= x*x*x + x - 1 starting at 0.5:",
--      FixedPointTransform(f1,1.1))

print("the fixed point of g(x)= 1/1+x*x starting at 1:",
     FixedPointTransform(g,1))
--Exercise 1.35 Compute the golden ration as a fixed point of
--  the transformation x-> 1+1/x


function deriv(g)  --deriv returns function so had to assign to
                   --function variable then use that to get value.
   local dx=0.00001
   return function (x) return (g(x+dx)-g(x))/dx end
end

function fib(x) return 1+(1/x)
end
print("the fixed point of x->1+1/x starting at 1 is ",
      FixedPointTransform(fib,1))
local log=math.log
function lg(x) return log(1000)/log(x) end

print("the fixed point of x -> log 1000/log x is: ",
    FixedPointTransform(lg,1.1))

--Newton's Method
function NewtonMethod(fnc, x0)
   local FPT=FixedPointTransform
   local d=deriv
   function NewtonTransform(g)
      local Dg=d(g)
      return function(x) return (x-(g(x)/Dg(x))) end
   end
   local NT=NewtonTransform
   return FPT(NT(fnc),x0)
end

function f2(y) return y*y*y-5 end

print("the root of x^3 - 5 is ",
      NewtonMethod(f2,3))

   
--Secant method for finding roots
-- let f be the function whose roots are unknown
-- let x0,x1 be initial values
--then the recurrence relation
--     xn= xn-1 - f(xn-1)((xn-1  - xn-2))/(f(xn-1)-f(xn-2))
--defines the secant method

function y(x) return x*x-3 end  -- the function x^2-3
--want to find sqrt(3)
function secantMethod(f,x1)
   local eps=0.00001  --tolerance
   local x2=f(x1) -- other initial value
   local curval= (x1*f(x2) - x2*f(x1))/(f(x2) -f(x1))
   while math.abs(curval - x2)> eps do
      x1=x2
      x2=curval
      curval= (x1*f(x2) - x2*f(x1))/(f(x2) -f(x1))
   end
   return curval
end
print("the root of x^2 - 3 is ",secantMethod(y,2))

--g should be derivative of target
--start .
function gradDescent(g,start)
   local cur_x=start
   local gamma=0.01
   local delta=0.00001
   local prev_step_size=1
   local max_iters=10000
   local iters=0
   local prev_x=0
   local abs=math.abs
   local df=g
   while prev_step_size > delta and iters < max_iters do
      prev_x=cur_x
      cur_x= cur_x - gamma * df(prev_x)
      prev_step_size = abs(cur_x - prev_x)
      iters=iters +1
   end
   print("the local minimum occurs at ", cur_x)
end
local df=function(x) return 4*x*x*x -9*x*x end
gradDescent(df,6)


