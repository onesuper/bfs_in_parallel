
for i in $(seq 4 12)

do

# test the correctness of sockets

./sockets ../../test_case/tiny_graph.txt $i


# regular
./sockets ../../test_case/regular/RGL1 $i
#./sockets ../../test_case/regular/RGL2 $i
#./sockets ../../test_case/regular/RGL3 $i
#./sockets ../../test_case/regular/RGL4 $i
#./sockets ../../test_case/regular/RGL5 $i
#./sockets ../../test_case/regular/RGL6 $i
#./sockets ../../test_case/regular/RGL7 $i
#./sockets ../../test_case/regular/RGL8 $i
#./sockets ../../test_case/regular/RGL9 $i
#./sockets ../../test_case/regular/RGL10 $i


# irregular
./sockets ../../test_case/irregular/IRGL1 $i
#./sockets ../../test_case/irregular/IRGL2 $i
#./sockets ../../test_case/irregular/IRGL3 $i
#./sockets ../../test_case/irregular/IRGL4 $i
#./sockets ../../test_case/irregular/IRGL5 $i
#./sockets ../../test_case/irregular/IRGL6 $i
#./sockets ../../test_case/irregular/IRGL7 $i
#./sockets ../../test_case/irregular/IRGL8 $i
#./sockets ../../test_case/irregular/IRGL9 $i
#./sockets ../../test_case/irregular/IRGL10 $i



# test by real graph
./sockets ../../test_case/real_graph/BAY $i
#./sockets ../../test_case/real_graph/NY $i
#./sockets ../../test_case/real_graph/COL $i
#./sockets ../../test_case/real_graph/FLA $i
#./sockets ../../test_case/real_graph/CAL $i
#./sockets ../../test_case/real_graph/NE $i
#./sockets ../../test_case/real_graph/NW $i
#./sockets ../../test_case/real_graph/LKS $i
#./sockets ../../test_case/real_graph/E $i
#./sockets ../../test_case/real_graph/W $i
#./sockets ../../test_case/real_graph/CTR $i
#./sockets ../../test_case/real_graph/USA $i


# small world

./sockets ../../test_case/small_world/SW1 $i
#./sockets ../../test_case/small_world/SW2 $i
#./sockets ../../test_case/small_world/SW3 $i
#./sockets ../../test_case/small_world/SW4 $i
#./sockets ../../test_case/small_world/SW5 $i
#./sockets ../../test_case/small_world/SW6 $i
#./sockets ../../test_case/small_world/SW7 $i
#./sockets ../../test_case/small_world/SW8 $i
#./sockets ../../test_case/small_world/SW9 $i
#./sockets ../../test_case/small_world/SW10 $i


done
