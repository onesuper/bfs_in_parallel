
for i in 1, 2, 4, 8, 16

do

# test the correctness of check

#./check ../../test_case/tiny_graph $i


# regular
#./check ../../test_case/regular/RGL1 $i
#./check ../../test_case/regular/RGL2 $i
#./check ../../test_case/regular/RGL3 $i
#./check ../../test_case/regular/RGL4 $i
./check ../../test_case/regular/RGL5 $i
#./check ../../test_case/regular/RGL6 $i
#./check ../../test_case/regular/RGL7 $i
#./check ../../test_case/regular/RGL8 $i
#./check ../../test_case/regular/RGL9 $i
#./check ../../test_case/regular/RGL10 $i


# irregular
#./check ../../test_case/irregular/IRGL1 $i
#./check ../../test_case/irregular/IRGL2 $i
#./check ../../test_case/irregular/IRGL3 $i
#./check ../../test_case/irregular/IRGL4 $i
./check ../../test_case/irregular/IRGL5 $i
#./check ../../test_case/irregular/IRGL6 $i
#./check ../../test_case/irregular/IRGL7 $i
#./check ../../test_case/irregular/IRGL8 $i
#./check ../../test_case/irregular/IRGL9 $i
#./check ../../test_case/irregular/IRGL10 $i



# test by real graph
#./check ../../test_case/real_graph/BAY $i
#./check ../../test_case/real_graph/NY $i
#./check ../../test_case/real_graph/COL $i
#./check ../../test_case/real_graph/FLA $i
./check ../../test_case/real_graph/CAL $i
#./check ../../test_case/real_graph/NE $i
#./check ../../test_case/real_graph/NW $i
#./check ../../test_case/real_graph/LKS $i
#./check ../../test_case/real_graph/E $i
#./check ../../test_case/real_graph/W $i
#./check ../../test_case/real_graph/CTR $i
#./check ../../test_case/real_graph/USA $i


# small world

#./check ../../test_case/small_world/SW1 $i
#./check ../../test_case/small_world/SW2 $i
#./check ../../test_case/small_world/SW3 $i
#./check ../../test_case/small_world/SW4 $i
./check ../../test_case/small_world/SW5 $i
#./check ../../test_case/small_world/SW6 $i
#./check ../../test_case/small_world/SW7 $i
#./check ../../test_case/small_world/SW8 $i
#./check ../../test_case/small_world/SW9 $i
#./check ../../test_case/small_world/SW10 $i


done
