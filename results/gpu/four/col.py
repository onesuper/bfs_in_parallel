import string


file = open('3.out')

file2 = open('3.dat','w')


lines = file.readlines() 

N = 11


for j in range(0, len(lines)):
    
    list = lines[j].split()

    if j%N == 0 and j != 0:
       file2.write('\n')
    file2.write(str(string.atof(list[5])*1000) + ' ')

        
    
    
