

# correctness
for i in $(seq 1 6)
do
	./baseline ./../../test_case/tiny_graph.txt $i
done
# real graph

#for i in $(seq 1 30)
#do
#	./baseline ./../../test_case/real_graph/USA-road-d.CAL.out $i
#done

#./baseline ./../../test_case/real_graph/USA-road-d.CTR.out 1
