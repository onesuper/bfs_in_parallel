
for i in $(seq 1 100)

do

# test the correctness of conflict

#./conflict ../../test_case/tiny_graph 6


# regular
./conflict ../../test_case/regular/RGL1 $i
#./conflict ../../test_case/regular/RGL2 $i
#./conflict ../../test_case/regular/RGL3 $i
#./conflict ../../test_case/regular/RGL4 $i
#./conflict ../../test_case/regular/RGL5 $i
#./conflict ../../test_case/regular/RGL6 $i
#./conflict ../../test_case/regular/RGL7 $i
#./conflict ../../test_case/regular/RGL8 $i
#./conflict ../../test_case/regular/RGL9 $i
#./conflict ../../test_case/regular/RGL10 $i


# irregular
./conflict ../../test_case/irregular/IRGL1 $i
#./conflict ../../test_case/irregular/IRGL2 $i
#./conflict ../../test_case/irregular/IRGL3 $i
#./conflict ../../test_case/irregular/IRGL4 $i
#./conflict ../../test_case/irregular/IRGL5 $i
#./conflict ../../test_case/irregular/IRGL6 $i
#./conflict ../../test_case/irregular/IRGL7 $i
#./conflict ../../test_case/irregular/IRGL8 $i
#./conflict ../../test_case/irregular/IRGL9 $i
#./conflict ../../test_case/irregular/IRGL10 $i



# test by real graph
./conflict ../../test_case/real_graph/BAY $i
#./conflict ../../test_case/real_graph/NY $i
#./conflict ../../test_case/real_graph/COL $i
#./conflict ../../test_case/real_graph/FLA $i
#./conflict ../../test_case/real_graph/CAL $i
#./conflict ../../test_case/real_graph/NE $i
#./conflict ../../test_case/real_graph/NW $i
#./conflict ../../test_case/real_graph/LKS $i
#./conflict ../../test_case/real_graph/E $i
#./conflict ../../test_case/real_graph/W $i
#./conflict ../../test_case/real_graph/CTR $i
#./conflict ../../test_case/real_graph/USA $i


# small world

./conflict ../../test_case/small_world/SW1 $i
#./conflict ../../test_case/small_world/SW2 $i
#./conflict ../../test_case/small_world/SW3 $i
#./conflict ../../test_case/small_world/SW4 $i
#./conflict ../../test_case/small_world/SW5 $i
#./conflict ../../test_case/small_world/SW6 $i
#./conflict ../../test_case/small_world/SW7 $i
#./conflict ../../test_case/small_world/SW8 $i
#./conflict ../../test_case/small_world/SW9 $i
#./conflict ../../test_case/small_world/SW10 $i


done
