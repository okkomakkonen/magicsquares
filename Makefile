naive:
	g++ naive.cpp -o naive
	nohup ./naive > squares.txt &

better:
	g++ better.cpp -o better
	nohup ./better > squares.txt &

best:
	g++ best.cpp factors.cpp -o best
	nohup ./best > squares.txt &
