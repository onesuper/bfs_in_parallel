
for i in $(seq 2 2)

do

# test the correctness of baseline1

./baseline1 ../../test_case/tiny_graph $i


# regular
./baseline1 ../../test_case/regular/RGL1 $i
./baseline1 ../../test_case/regular/RGL2 $i
#./baseline1 ../../test_case/regular/RGL3 
#./baseline1 ../../test_case/regular/RGL4 
#./baseline1 ../../test_case/regular/RGL5
#./baseline1 ../../test_case/regular/RGL6
#./baseline1 ../../test_case/regular/RGL7
#./baseline1 ../../test_case/regular/RGL8
#./baseline1 ../../test_case/regular/RGL9
#./baseline1 ../../test_case/regular/RGL10


# irregular
./baseline1 ../../test_case/irregular/IRGL1 $i
./baseline1 ../../test_case/irregular/IRGL2 $i
#./baseline1 ../../test_case/irregular/IRGL3
#./baseline1 ../../test_case/irregular/IRGL4
#./baseline1 ../../test_case/irregular/IRGL5
#./baseline1 ../../test_case/irregular/IRGL6
#./baseline1 ../../test_case/irregular/IRGL7
#./baseline1 ../../test_case/irregular/IRGL8
#./baseline1 ../../test_case/irregular/IRGL9
#./baseline1 ../../test_case/irregular/IRGL10



# test by real graph
./baseline1 ../../test_case/real_graph/BAY $i
./baseline1 ../../test_case/real_graph/NY $i
#./baseline1 ../../test_case/real_graph/COL
#./baseline1 ../../test_case/real_graph/FLA
#./baseline1 ../../test_case/real_graph/CAL
#./baseline1 ../../test_case/real_graph/NE
#./baseline1 ../../test_case/real_graph/NW
#./baseline1 ../../test_case/real_graph/LKS
#./baseline1 ../../test_case/real_graph/E
#./baseline1 ../../test_case/real_graph/W
#./baseline1 ../../test_case/real_graph/CTR
#./baseline1 ../../test_case/real_graph/USA


# small world

./baseline1 ../../test_case/small_world/SW1 $i
./baseline1 ../../test_case/small_world/SW2 $i
#./baseline1 ../../test_case/small_world/SW3
#./baseline1 ../../test_case/small_world/SW4
#./baseline1 ../../test_case/small_world/SW5
#./baseline1 ../../test_case/small_world/SW6
#./baseline1 ../../test_case/small_world/SW7
#./baseline1 ../../test_case/small_world/SW8
#./baseline1 ../../test_case/small_world/SW9
#./baseline1 ../../test_case/small_world/SW10


done
