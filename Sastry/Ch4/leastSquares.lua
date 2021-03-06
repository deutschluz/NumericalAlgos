function solveSystem(Eq1,Eq2)
  local pivot1=Eq1[1]
  if pivot1 ~= 1 then
    for i=1,#Eq1 do
      Eq1[i]=Eq1[i]/pivot1
    end
  end
  local first2=Eq2[1]
  if first2 ~= 0 then
    for i=1,#Eq2 do
      Eq2[i]=Eq2[i]-first2*Eq1[i]
    end
  end
  local pivot3=Eq2[2]
  if pivot3 ~= 1 then
    for i=1,#Eq2 do
      Eq2[i]=Eq2[2]/pivot3
    end
  end
  local second1=Eq1[2]
  if second1 ~=0 then
    for i=1,#Eq1 do
      Eq1[i]=Eq1[i]-second1*Eq2[2]
    end
  end
  for i=1,#Eq1 do
    print(Eq1[i],Eq2[i])
  end
end

function printTable()
  l={800.3,800.4,800.6,800.7,800.9,801.0}
  T={20,30,40,50,60,70}
  local sqT=0;local ll=0;local Tot=0;local prod=0
  for i=1,#l do
    ll= ll+l[i]
    sqT=sqT+T[i]*T[i]
    Tot=Tot + T[i]
    prod=prod + T[i]*l[i]
    print(l[i],T[i],T[i]*T[i],T[i]*l[i])
  end
  print("==========")
  print(ll,Tot,sqT,prod)
  E1={6,270,4803.9}
  E2={270,13900,216201}
  solveSystem(E1,E2)
end

printTable()
