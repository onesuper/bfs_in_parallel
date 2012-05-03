file = open('BAY')

file2 = open('BAY.out','w')

import string

lines = file.readlines()


list1 = lines[0].split()
list2 = lines[1].split()
list3 = lines[2].split()


for i in range(1, 12):
    list2[i] = str(string.atof(list1[i])/string.atof(list2[i]) )
    list3[i] = str(string.atof(list1[i])/string.atof(list3[i]) )
    list1[i] = '1'



for i in range(0, 12):
    string0 = str(2**(i-1)) + ' ' + list1[i] + ' ' + list2[i] + ' ' + list3[i] + '\n'
    file2.write(string0)
