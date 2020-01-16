naive:
	g++ naive.cpp -o naive.o
	nohup ./naive.o > squares.txt &

better:
	g++ better.cpp -o better.o
	nohup ./better.o > squares.txt &
