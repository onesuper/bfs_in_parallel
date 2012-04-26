
for i in $(seq 1 20)

do

# test the correctness of concurrent3

#./concurrent3 ../../test_case/tiny_graph $i


# regular
./concurrent3 ../../test_case/regular/RGL1 $i
#./concurrent3 ../../test_case/regular/RGL2 $i
#./concurrent3 ../../test_case/regular/RGL3 $i
#./concurrent3 ../../test_case/regular/RGL4 $i
#./concurrent3 ../../test_case/regular/RGL5 $i
#./concurrent3 ../../test_case/regular/RGL6 $i
#./concurrent3 ../../test_case/regular/RGL7 $i
#./concurrent3 ../../test_case/regular/RGL8 $i
#./concurrent3 ../../test_case/regular/RGL9 $i
#./concurrent3 ../../test_case/regular/RGL10 $i


# irregular
./concurrent3 ../../test_case/irregular/IRGL1 $i
#./concurrent3 ../../test_case/irregular/IRGL2 $i
#./concurrent3 ../../test_case/irregular/IRGL3 $i
#./concurrent3 ../../test_case/irregular/IRGL4 $i
#./concurrent3 ../../test_case/irregular/IRGL5 $i
#./concurrent3 ../../test_case/irregular/IRGL6 $i
#./concurrent3 ../../test_case/irregular/IRGL7 $i
#./concurrent3 ../../test_case/irregular/IRGL8 $i
#./concurrent3 ../../test_case/irregular/IRGL9 $i
#./concurrent3 ../../test_case/irregular/IRGL10 $i



# test by real graph
./concurrent3 ../../test_case/real_graph/BAY $i
#./concurrent3 ../../test_case/real_graph/NY $i
#./concurrent3 ../../test_case/real_graph/COL $i
#./concurrent3 ../../test_case/real_graph/FLA $i
#./concurrent3 ../../test_case/real_graph/CAL $i
#./concurrent3 ../../test_case/real_graph/NE $i
#./concurrent3 ../../test_case/real_graph/NW $i
#./concurrent3 ../../test_case/real_graph/LKS $i
#./concurrent3 ../../test_case/real_graph/E $i
#./concurrent3 ../../test_case/real_graph/W $i
#./concurrent3 ../../test_case/real_graph/CTR $i
#./concurrent3 ../../test_case/real_graph/USA $i


# small world

./concurrent3 ../../test_case/small_world/SW1 $i
#./concurrent3 ../../test_case/small_world/SW2 $i
#./concurrent3 ../../test_case/small_world/SW3 $i
#./concurrent3 ../../test_case/small_world/SW4 $i
#./concurrent3 ../../test_case/small_world/SW5 $i
#./concurrent3 ../../test_case/small_world/SW6 $i
#./concurrent3 ../../test_case/small_world/SW7 $i
#./concurrent3 ../../test_case/small_world/SW8 $i
#./concurrent3 ../../test_case/small_world/SW9 $i
#./concurrent3 ../../test_case/small_world/SW10 $i


done
