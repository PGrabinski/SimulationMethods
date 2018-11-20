output: main.o helper.o lattice.o rng.o measurer.o wolfer.o
	g++ Source/*.o -std=c++17 -lgsl -lm -lgslcblas -fopenmp -o wolf_sim

main.o: Source/main.cpp
	g++ -c Source/main.cpp -std=c++17 -lgsl -lm -lgslcblas -o Source/main.o

helper.o: Source/helper.cpp Source/helper.h
	g++ -c Source/helper.cpp -std=c++17 -lgsl -lm -lgslcblas -o Source/helper.o

lattice.o: Source/lattice.cpp Source/lattice.h
	g++ -c Source/lattice.cpp -std=c++17 -lgsl -lm -lgslcblas -o Source/lattice.o

measurer.o: Source/measurer.cpp Source/measurer.h
	g++ -c Source/measurer.cpp -std=c++17 -lgsl -lm -lgslcblas -o Source/measurer.o

rng.o: Source/rng.cpp Source/rng.h
	g++ -c Source/rng.cpp -std=c++17 -lgsl -lm -lgslcblas -o Source/rng.o

wolfer.o: Source/wolfer.cpp Source/wolfer.h
	g++ -c Source/wolfer.cpp -std=c++17 -fopenmp -lgsl -lm -lgslcblas -o Source/wolfer.o
	
clean:
	rm Source/*.o wolf_sim