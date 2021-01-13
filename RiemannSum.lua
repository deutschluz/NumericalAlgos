--a lua implementation of the famous Riemann Sums from calculus.
--dbg= require("debugger")

function avg(x,y) return (x+y)/2 end


function RiemannSum(f,L,R,numOfTerms)
  local avg=avg
  local total=0
  local deltaX=(R-L)/numOfTerms
  local midP=avg(L+deltaX,L)
  for i=midP,R,deltaX do
     total=total + f(midP)
     midP=midP+deltaX
  end
  return deltaX*total
end

function SimpsonSum(f,L,R,numOfTerms)
   local deltaX=(R-L)/numOfTerms
   local total = 0
   local K=0
   local count=0;
  -- dbg()
   for i=L,R,deltaX do
      count=count+1
      if i==L or i==R then K=1;total=total + K*f(i)
      elseif count%2==1 then K=4;total=total + K*f(i)
      else K=2;total=total + K*f(i)
      end
   end
   return (deltaX/3)*total;
end

function f1(x) return 1/x end
print("using N=10, the integral of 1/x from 1,2 by deltaX=0.1 is",
      SimpsonSum(f1,1,2,10))

function TrapezoidSum(f,L,R,numOfTerms)
   local deltaX=(R-L)/numOfTerms
   local total = 0
--   dbg()
   for i=L,R,deltaX do
      if i==L or i==R then total=total + f(i)
      else total=total + 2*f(i)
      end
   end
   return (deltaX/2)*total;
end




--Devise an "Integral" function that can use any method to sum
-- the integral as a subroutine. Further the "integral" function
-- should have a parameter epsilon for determining when to
-- terminate the calculation by calculating the difference between
-- the current result and the previous.

function Integral(f,L,R,epsilon)
   local RS=RiemannSum
   local prevRes=0
   local numOfTerms=1
   local result=RS(f,L,R,numOfTerms) --start at N=5   local numOfTerms=6
   while result - prevRes >= epsilon do
      numOfTerms=numOfTerms+10
      prevRes=result
      result=RS(f,L,R,numOfTerms)
   end
   return result
end

function IntegralT(f,L,R,epsilon)
   local TS=TrapezoidSum
   local prevRes=0
   local numOfTerms=1
 --  dbg()
   local result=1

   while math.abs(result - prevRes) >= epsilon do
      numOfTerms=numOfTerms+1
      prevRes=result
  --    print("Results    NumberOf Terms")
  --    print(result,numOfTerms)
   
      result=TS(f,L,R,numOfTerms)
   end
   return result
end

function IntegralS(f,L,R,epsilon)
   local SS=SimpsonSum
   local prevRes=0
   local numOfTerms=1
   local result=1 --start at N=5   local numOfTerms=6
   while math.abs(result - prevRes) >= epsilon do
      numOfTerms=numOfTerms+1
      prevRes=result
 --     print("Results    NumberOf Terms")
 --     print(result,numOfTerms)
      
      result=SS(f,L,R,numOfTerms)
   --   print("result-prevRes",result-prevRes)
   end
   return result
end

--print("Integral of 1/x from 1 to 2 using RiemannSums is: ",Integral(f1,1,2,0.0000001))
--print("Integral of 1/x from 1 to 2 using SimpsonSums is: ",IntegralS(f1,1,2,0.0000001))
--print("Integral of 1/x from 1 to 2 using TrapezoidSums is: ",IntegralT(f1,1,2,0.0000001))
--print("for comparison, this integral should equal ln 2: ", math.log(2))

function g(x) return (1-x^3)^(1/3) end
function h(x) return (1-x^2)^(1/2) end
local threePI=4*IntegralT(g,0,1,0.0000001)
print(debug.traceback(print("Integral of (1-x^2)^1/2 from 0 to 1 using RiemannSums is: ",Integral(h,0,1,0.0000001))))
print("Integral of (1-x^3)^1/3 from 0 to 1 using TrapezoidSums is: ",threePI/4)
print("using the calculation above, 3pi/ is approximatedly", threePI)
print("and 3pi is ", threePI)
print("also for comparison pi/2 is ", math.pi)
--to determine whether this is some sort of constant of the 3Unit circle
-- we can compute arclength integrals





