

file = open('all_four')


file1 = open('1', 'w')
file2 = open('2', 'w')
file3 = open('3', 'w')
file4 = open('4', 'w')

i = 0


while True:
      for i in range(0,10):
          line = file.readline()
          if not line:
             break
          file1.write(line)

      for i in range(0, 10):
          line = file.readline()
          if not line:
             break
          file2.write(line)

      for i in range(0, 12):
          line = file.readline()
          if not line:
             break
          file3.write(line)

      for i in range(0, 10):
          line = file.readline()
          if not line:
             break
          file4.write(line)
      
         
  
