
for i in $(seq 1 100)

do

# test the correctness of baseline1

#./baseline1 ../../test_case/tiny_graph $i


# regular
./baseline1 ../../test_case/regular/RGL1 $i
#./baseline1 ../../test_case/regular/RGL2 $i
#./baseline1 ../../test_case/regular/RGL3 $i
#./baseline1 ../../test_case/regular/RGL4 $i
#./baseline1 ../../test_case/regular/RGL5 $i
#./baseline1 ../../test_case/regular/RGL6 $i
#./baseline1 ../../test_case/regular/RGL7 $i
#./baseline1 ../../test_case/regular/RGL8 $i
#./baseline1 ../../test_case/regular/RGL9 $i
#./baseline1 ../../test_case/regular/RGL10 $i


# irregular
./baseline1 ../../test_case/irregular/IRGL1 $i
#./baseline1 ../../test_case/irregular/IRGL2 $i
#./baseline1 ../../test_case/irregular/IRGL3 $i
#./baseline1 ../../test_case/irregular/IRGL4 $i
#./baseline1 ../../test_case/irregular/IRGL5 $i
#./baseline1 ../../test_case/irregular/IRGL6 $i
#./baseline1 ../../test_case/irregular/IRGL7 $i
#./baseline1 ../../test_case/irregular/IRGL8 $i
#./baseline1 ../../test_case/irregular/IRGL9 $i
#./baseline1 ../../test_case/irregular/IRGL10 $i



# test by real graph
./baseline1 ../../test_case/real_graph/BAY $i
#./baseline1 ../../test_case/real_graph/NY $i
#./baseline1 ../../test_case/real_graph/COL $i
#./baseline1 ../../test_case/real_graph/FLA $i
#./baseline1 ../../test_case/real_graph/CAL $i
#./baseline1 ../../test_case/real_graph/NE $i
#./baseline1 ../../test_case/real_graph/NW $i
#./baseline1 ../../test_case/real_graph/LKS $i
#./baseline1 ../../test_case/real_graph/E $i
#./baseline1 ../../test_case/real_graph/W $i
#./baseline1 ../../test_case/real_graph/CTR $i
#./baseline1 ../../test_case/real_graph/USA $i


# small world

./baseline1 ../../test_case/small_world/SW1 $i
#./baseline1 ../../test_case/small_world/SW2 $i
#./baseline1 ../../test_case/small_world/SW3 $i
#./baseline1 ../../test_case/small_world/SW4 $i
#./baseline1 ../../test_case/small_world/SW5 $i
#./baseline1 ../../test_case/small_world/SW6 $i
#./baseline1 ../../test_case/small_world/SW7 $i
#./baseline1 ../../test_case/small_world/SW8 $i
#./baseline1 ../../test_case/small_world/SW9 $i
#./baseline1 ../../test_case/small_world/SW10 $i


done
