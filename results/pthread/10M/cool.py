file = open('4')

file2 = open('4.out', 'w')

line0 = file.readline() 

a = []
b = []
c = []
d = []
e = []

a.append(line0)
b.append(line0)
c.append(line0)
d.append(line0)
e.append(line0)

while True:
      line = file.readline()
      if not line:
         break
      a.append(line)

      line = file.readline()
      if not line:
         break
      b.append(line)

      line = file.readline()
      if not line:
         break
      c.append(line)

      line = file.readline()
      if not line:
         break
      d.append(line)

      line = file.readline()
      if not line:
         break
      e.append(line)



for line in a:
    file2.write(line)


for line in b:
    file2.write(line)


for line in c:
    file2.write(line)


for line in d:
    file2.write(line)

for line in e:
    file2.write(line)
