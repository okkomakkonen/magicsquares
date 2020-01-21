clean:
	if [ -f "main" ]; then rm main; fi

naive:
	make clean
	g++ naive.cpp -o main
	nohup ./main > squares.txt &

better:
	make clean
	g++ better.cpp -o main
	nohup ./main > squares.txt &

best:
	make clean
	g++ best.cpp factors.cpp -o main
	nohup ./main > squares.txt &

new:
	make clean
	g++ new.cpp -o main
	nohup ./main > squares.txt &

multi:
	make clean
	g++ multithread.cpp -o main -pthread
	nohup ./main > squares.txt &
	
