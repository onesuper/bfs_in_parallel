

import string

name = "cpu_conflict_1to100"

file1 = open(name)


i = 0

a = []
b = []
c = []
d = []

while True:
      line = file1.readline()
      if not line:
         break
      
      list = line.split()
      if len(list) > 0:
         if i % 4 == 0 :
            a.append(string.atof(list[5]))
           
         elif i % 4 == 1:
            b.append(string.atof(list[5]))
           
         elif i % 4 == 2:
            c.append(string.atof(list[5]))
          
         else:
            d.append(string.atof(list[5]))
          
         i += 1


outfile = open(name+".dat", 'w')


i = 0
while i < 100:
      outfile.write(str(i+1)+' '+str(a[i]*1000) + " "+str(b[i]*1000) + " " + str(c[i]*1000) + " "  + str(d[i]*1000) + '\n')
      i += 1

