run:
	g++ naive.cpp -o naive.o
	nohup ./naive.o > squares.txt &
