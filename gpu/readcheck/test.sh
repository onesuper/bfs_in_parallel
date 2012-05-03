
for i in 1, 2, 4, 8, 16, 32, 64, 128, 256, 512, 1024

do

# test the correctness of readcheck

#./readcheck ../../test_case/tiny_graph $i


# regular
#./readcheck ../../test_case/regular/RGL1 $i
#./readcheck ../../test_case/regular/RGL2 $i
#./readcheck ../../test_case/regular/RGL3 $i
#./readcheck ../../test_case/regular/RGL4 $i
#./readcheck ../../test_case/regular/RGL5 $i
#./readcheck ../../test_case/regular/RGL6 $i
#./readcheck ../../test_case/regular/RGL7 $i
#./readcheck ../../test_case/regular/RGL8 $i
#./readcheck ../../test_case/regular/RGL9 $i
#./readcheck ../../test_case/regular/RGL10 $i


# irregular
#./readcheck ../../test_case/irregular/IRGL1 $i
#./readcheck ../../test_case/irregular/IRGL2 $i
#./readcheck ../../test_case/irregular/IRGL3 $i
#./readcheck ../../test_case/irregular/IRGL4 $i
#./readcheck ../../test_case/irregular/IRGL5 $i
#./readcheck ../../test_case/irregular/IRGL6 $i
#./readcheck ../../test_case/irregular/IRGL7 $i
#./readcheck ../../test_case/irregular/IRGL8 $i
#./readcheck ../../test_case/irregular/IRGL9 $i
#./readcheck ../../test_case/irregular/IRGL10 $i



# test by real graph
#./readcheck ../../test_case/real_graph/BAY $i
#./readcheck ../../test_case/real_graph/NY $i
#./readcheck ../../test_case/real_graph/COL $i
#./readcheck ../../test_case/real_graph/FLA $i
#./readcheck ../../test_case/real_graph/CAL $i
#./readcheck ../../test_case/real_graph/NE $i
#./readcheck ../../test_case/real_graph/NW $i
#./readcheck ../../test_case/real_graph/LKS $i
#./readcheck ../../test_case/real_graph/E $i
#./readcheck ../../test_case/real_graph/W $i
#./readcheck ../../test_case/real_graph/CTR $i
#./readcheck ../../test_case/real_graph/USA $i


# small world

./readcheck ../../test_case/small_world/SW1 $i
#./readcheck ../../test_case/small_world/SW2 $i
#./readcheck ../../test_case/small_world/SW3 $i
#./readcheck ../../test_case/small_world/SW4 $i
#./readcheck ../../test_case/small_world/SW5 $i
#./readcheck ../../test_case/small_world/SW6 $i
#./readcheck ../../test_case/small_world/SW7 $i
#./readcheck ../../test_case/small_world/SW8 $i
#./readcheck ../../test_case/small_world/SW9 $i
#./readcheck ../../test_case/small_world/SW10 $i


done
