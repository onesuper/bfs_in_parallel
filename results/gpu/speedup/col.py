import string


file = open('4.out')

file2 = open('4.dat','w')

file1 = open('4.naive')
org =file1.readlines()

for one in org:
    one = one[0:-1]

lines = file.readlines() 






new = [[] for i in range(0, 11)]

for j in range(0, len(lines)):
    
    list = lines[j].split()

    new[j%11].append(str(string.atof(org[j/11]) / string.atof(list[5])))



for line in new:
    for one in line:
        file2.write(' '+one)
    file2.write('\n')
    
    
