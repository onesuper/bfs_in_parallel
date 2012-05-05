file = open('4')
file2 = open('4.1', 'w')


lines = file.readlines()

import string

line = []

line.append(lines[0].split())
line.append(lines[1].split())
line.append(lines[2].split())
line.append(lines[3].split())
line.append(lines[4].split())



for i in range(0, 5):
    line[i][2] = str(string.atof(line[i][1]) / string.atof(line[i][2]))
    line[i][3] = str(string.atof(line[i][1]) / string.atof(line[i][3]))
    line[i][4] = str(string.atof(line[i][1]) / string.atof(line[i][4]))
    line[i][5] = str(string.atof(line[i][1]) / string.atof(line[i][5]))
    line[i][1] = '1'


for i in range(0, 5):
    for j in range(0, 6):
        file2.write(line[i][j] + ' ')
    file2.write('\n')
