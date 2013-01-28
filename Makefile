CPP=clang++
OPT=-O3
benchmarks: benchmark_c benchmark_cinline benchmark_cpp

benchmark_c: benchmark_c.cpp qsort-complete.o
	$(CPP) $(OPT) $^ -o $@

benchmark_cinline: benchmark_cinline.cpp qsort-complete.o
	$(CPP) $(OPT) $^ -o $@

benchmark_cpp: benchmark_cpp.cpp qsort-complete.o
	$(CPP) $(OPT) $^ -o $@

qsort-complete.o: qsort-complete.c qsort-complete.h qsort-inline.h
	$(CPP) $(OPT) -c $< -o $@

clean:
	- rm benchmark_c benchmark_cpp benchmark_cinline *.o
