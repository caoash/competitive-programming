for((i = 1; ; ++i)); do
    echo $i
    ./gen-tree $i > int
    ./NOI07-Dragon < int > out1
    # ./brute < int > out2
     # diff -w out1 out2 || break
     #diff -w <(./a < int) <(./brute < int) || break
done
