
for i in $(seq 1 30)

do

# test the correctness of baseline2

#./baseline2 ../../test_case/tiny_graph 6


# regular
./baseline2 ../../test_case/regular/RGL1 $i
#./baseline2 ../../test_case/regular/RGL2 $i
#./baseline2 ../../test_case/regular/RGL3 $i
#./baseline2 ../../test_case/regular/RGL4 $i
#./baseline2 ../../test_case/regular/RGL5 $i
#./baseline2 ../../test_case/regular/RGL6 $i
#./baseline2 ../../test_case/regular/RGL7 $i
#./baseline2 ../../test_case/regular/RGL8 $i
#./baseline2 ../../test_case/regular/RGL9 $i
#./baseline2 ../../test_case/regular/RGL10 $i


# irregular
./baseline2 ../../test_case/irregular/IRGL1 $i
#./baseline2 ../../test_case/irregular/IRGL2 $i
#./baseline2 ../../test_case/irregular/IRGL3 $i
#./baseline2 ../../test_case/irregular/IRGL4 $i
#./baseline2 ../../test_case/irregular/IRGL5 $i
#./baseline2 ../../test_case/irregular/IRGL6 $i
#./baseline2 ../../test_case/irregular/IRGL7 $i
#./baseline2 ../../test_case/irregular/IRGL8 $i
#./baseline2 ../../test_case/irregular/IRGL9 $i
#./baseline2 ../../test_case/irregular/IRGL10 $i



# test by real graph
./baseline2 ../../test_case/real_graph/BAY $i
#./baseline2 ../../test_case/real_graph/NY $i
#./baseline2 ../../test_case/real_graph/COL $i
#./baseline2 ../../test_case/real_graph/FLA $i
#./baseline2 ../../test_case/real_graph/CAL $i
#./baseline2 ../../test_case/real_graph/NE $i
#./baseline2 ../../test_case/real_graph/NW $i
#./baseline2 ../../test_case/real_graph/LKS $i
#./baseline2 ../../test_case/real_graph/E $i
#./baseline2 ../../test_case/real_graph/W $i
#./baseline2 ../../test_case/real_graph/CTR $i
#./baseline2 ../../test_case/real_graph/USA $i


# small world

./baseline2 ../../test_case/small_world/SW1 $i
#./baseline2 ../../test_case/small_world/SW2 $i
#./baseline2 ../../test_case/small_world/SW3 $i
#./baseline2 ../../test_case/small_world/SW4 $i
#./baseline2 ../../test_case/small_world/SW5 $i
#./baseline2 ../../test_case/small_world/SW6 $i
#./baseline2 ../../test_case/small_world/SW7 $i
#./baseline2 ../../test_case/small_world/SW8 $i
#./baseline2 ../../test_case/small_world/SW9 $i
#./baseline2 ../../test_case/small_world/SW10 $i


done
