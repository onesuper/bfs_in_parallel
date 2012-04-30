
for i in 1, 2, 4, 8, 16

do

# test the correctness of batch

#./batch ../../test_case/tiny_graph $i


# regular
#./batch ../../test_case/regular/RGL1 $i
#./batch ../../test_case/regular/RGL2 $i
#./batch ../../test_case/regular/RGL3 $i
#./batch ../../test_case/regular/RGL4 $i
#./batch ../../test_case/regular/RGL5 $i
#./batch ../../test_case/regular/RGL6 $i
#./batch ../../test_case/regular/RGL7 $i
#./batch ../../test_case/regular/RGL8 $i
#./batch ../../test_case/regular/RGL9 $i
./batch ../../test_case/regular/RGL10 $i


# irregular
#./batch ../../test_case/irregular/IRGL1 $i
#./batch ../../test_case/irregular/IRGL2 $i
#./batch ../../test_case/irregular/IRGL3 $i
#./batch ../../test_case/irregular/IRGL4 $i
#./batch ../../test_case/irregular/IRGL5 $i
#./batch ../../test_case/irregular/IRGL6 $i
#./batch ../../test_case/irregular/IRGL7 $i
#./batch ../../test_case/irregular/IRGL8 $i
#./batch ../../test_case/irregular/IRGL9 $i
./batch ../../test_case/irregular/IRGL10 $i



# test by real graph
#./batch ../../test_case/real_graph/BAY $i
#./batch ../../test_case/real_graph/NY $i
#./batch ../../test_case/real_graph/COL $i
#./batch ../../test_case/real_graph/FLA $i
#./batch ../../test_case/real_graph/CAL $i
#./batch ../../test_case/real_graph/NE $i
#./batch ../../test_case/real_graph/NW $i
#./batch ../../test_case/real_graph/LKS $i
#./batch ../../test_case/real_graph/E $i
#./batch ../../test_case/real_graph/W $i
#./batch ../../test_case/real_graph/CTR $i
./batch ../../test_case/real_graph/USA $i


# small world

#./batch ../../test_case/small_world/SW1 $i
#./batch ../../test_case/small_world/SW2 $i
#./batch ../../test_case/small_world/SW3 $i
#./batch ../../test_case/small_world/SW4 $i
#./batch ../../test_case/small_world/SW5 $i
#./batch ../../test_case/small_world/SW6 $i
#./batch ../../test_case/small_world/SW7 $i
#./batch ../../test_case/small_world/SW8 $i
#./batch ../../test_case/small_world/SW9 $i
./batch ../../test_case/small_world/SW10 $i


done
