clean:
	if [ -f "main" ]; then rm main; fi

algo1:
	make clean
	g++ algorithms/algo1.cpp -o main

algo2:
	make clean
	g++ algorithms/algo2.cpp -o main

algo3:
	make clean
	g++ algorithms/algo3.cpp -o main

algo4:
	make clean
	g++ algorithms/algo4.cpp -o main -pthread

algo5:
	make clean
	g++ algorithms/algo5.cpp -o main -pthread

test5:
	make clean
	g++ tests/test5.cpp -o test
