for((i = 1; ; ++i)); do
    echo $i
    ./gen $i > int
    ./POI-18-Metro < int > out1
     #diff -w <(./a < int) <(./brute < int) || break
done
