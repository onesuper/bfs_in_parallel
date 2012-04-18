
for i in $(seq 1 100)

do

# test the correctness of baseline2

#./baseline2 ../../test_case/tiny_graph 6


# regular
./non-lock ../../test_case/regular/RGL1 $i
#./non-lock ../../test_case/regular/RGL2 $i
#./non-lock ../../test_case/regular/RGL3 $i
#./non-lock ../../test_case/regular/RGL4 $i
#./non-lock ../../test_case/regular/RGL5 $i
#./non-lock ../../test_case/regular/RGL6 $i
#./non-lock ../../test_case/regular/RGL7 $i
#./non-lock ../../test_case/regular/RGL8 $i
#./non-lock ../../test_case/regular/RGL9 $i
#./non-lock ../../test_case/regular/RGL10 $i


# irregular
./non-lock ../../test_case/irregular/IRGL1 $i
#./non-lock ../../test_case/irregular/IRGL2 $i
#./non-lock ../../test_case/irregular/IRGL3 $i
#./non-lock ../../test_case/irregular/IRGL4 $i
#./non-lock ../../test_case/irregular/IRGL5 $i
#./non-lock ../../test_case/irregular/IRGL6 $i
#./non-lock ../../test_case/irregular/IRGL7 $i
#./non-lock ../../test_case/irregular/IRGL8 $i
#./non-lock ../../test_case/irregular/IRGL9 $i
#./non-lock ../../test_case/irregular/IRGL10 $i



# test by real graph
./non-lock ../../test_case/real_graph/BAY $i
#./non-lock ../../test_case/real_graph/NY $i
#./non-lock ../../test_case/real_graph/COL $i
#./non-lock ../../test_case/real_graph/FLA $i
#./non-lock ../../test_case/real_graph/CAL $i
#./non-lock ../../test_case/real_graph/NE $i
#./non-lock ../../test_case/real_graph/NW $i
#./non-lock ../../test_case/real_graph/LKS $i
#./non-lock ../../test_case/real_graph/E $i
#./non-lock ../../test_case/real_graph/W $i
#./non-lock ../../test_case/real_graph/CTR $i
#./non-lock ../../test_case/real_graph/USA $i


# small world

./non-lock ../../test_case/small_world/SW1 $i
#./non-lock ../../test_case/small_world/SW2 $i
#./non-lock ../../test_case/small_world/SW3 $i
#./non-lock ../../test_case/small_world/SW4 $i
#./non-lock ../../test_case/small_world/SW5 $i
#./non-lock ../../test_case/small_world/SW6 $i
#./non-lock ../../test_case/small_world/SW7 $i
#./non-lock ../../test_case/small_world/SW8 $i
#./non-lock ../../test_case/small_world/SW9 $i
#./non-lock ../../test_case/small_world/SW10 $i


done
