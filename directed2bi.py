#!/usr/bin
# tansfrom a directed graph to a bidirected graph


import string

filename = "test.txt"


infile = open(filename, 'r')


infile.readline()
infile.readline()
line = infile.readline()
line = line[0:-1]
list = line.split(" ")
node_num = string.atoi(list[2])
edge_num = string.atoi(list[4])
infile.readline()



graph = []

i = 0
while i < node_num:
      graph.append([])
      i += 1 

while True:
      line = infile.readline()
      if not line:
         break
      line = line[0:-1]
      list = line.split('\t')
      node_from = string.atoi(list[0])
      node_to = string.atoi(list[1]) 
      graph[node_from].append(node_to)
      graph[node_to].append(node_from)
    

infile.close()

'''
i = 0      
for line in graph:
    print i,
    print line
    i += 1
''' 

outfile = open(filename + ".2", 'w')

outfile.write("#blabla\n#blablabla...\n")

outfile.write("# Nodes: " + str(node_num) + " Edges: " + str(edge_num))
outfile.write("\nblabla\n")

i = 0
for line in graph:
    for one in line:
        outfile.write(str(i) + '\t' + str(one) + '\n') 
    i += 1


print 'done'
