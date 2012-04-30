file = open('4.out')

file2 = open('4.outdoor', 'w')


import string

while True:

      line = file.readline()
      if not line:
         break
      list = line.split()
      newline = list[0] + ' ' + str(string.atof(list[5])* 1000) + '\n'
      file2.write(newline)
