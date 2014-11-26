for i in 100 200 500 750 1000 1500 2000 2500 3000 4000 5000 6000 8000 10000 12000 15000 20000 25000 30000 50000 100000
do
  python gen.py $i > input.txt

  for method in 1 2 3 4
  do
    echo $i $method
    printf "$i $method 1 " >> result.txt
    ./speed $method input.txt 1 >> result.txt

    inc=$(python fac.py $i)
    printf "$i $method n " >> result.txt
    ./speed $method input.txt $inc >> result.txt
  done
done
