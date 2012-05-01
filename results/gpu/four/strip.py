

file = open('3')

file2 = open('3.out', 'w')




N = 12
list = [[] for i in range(0, N)]

lines = file.readlines()

i = 0
for line in lines:
    list[i%N].append(line)
    i+=1



for i in range(0, N):
    for line in list[i]:
        file2.write(line)
