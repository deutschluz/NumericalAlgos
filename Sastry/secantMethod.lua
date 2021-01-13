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
