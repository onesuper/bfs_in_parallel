
file1 = open("cpu_baseline_2to100")


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
            a.append(list[6])
            print "a", i
         elif i % 4 == 1:
            b.append(list[6])
            print "b", i
         elif i % 4 == 2:
            c.append(list[6])
            print "c", i
         else:
            d.append(list[6])
            print "d", i
         i += 1
        

print a 
print b
print c
print d


outfile = open("out", 'w')


for one in a:
    outfile.write(str(one) + "\n")

outfile.write('\n')

for one in b:
    outfile.write(str(one) + "\n")

outfile.write('\n')


for one in c:
    outfile.write(str(one) + "\n")

outfile.write('\n')


for one in d:
    outfile.write(str(one) + "\n")

outfile.write('\n')

