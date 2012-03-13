# test the correctness of naive

./naive ../test_case/tiny_graph.txt


# test by real graph
#./naive ../test_case/real_graph/USA-road-d.BAY.out

for i in $(seq 1 10)
do
	./naive ../test_case/real_graph/USA-road-d.CAL.out
done
#./naive ../test_case/real_graph/USA-road-d.COL.out
#./naive ../test_case/real_graph/USA-road-d.CTR.out
#./naive ../test_case/real_graph/USA-road-d.E.out
#./naive ../test_case/real_graph/USA-road-d.FLA.out
#./naive ../test_case/real_graph/USA-road-d.LKS.out
#./naive ../test_case/real_graph/USA-road-d.NE.out
#./naive ../test_case/real_graph/USA-road-d.NW.out
#./naive ../test_case/real_graph/USA-road-d.NY.out
#./naive ../test_case/real_graph/USA-road-d.USA.out
#./naive ../test_case/real_graph/USA-road-d.W.out

