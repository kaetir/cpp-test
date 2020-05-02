.PHONY: run clean all

all: foreach sort foreach_unseq fill 

chrono.o:
	g++ -std=c++17 -c -Wall libs/simple_chrono.cpp -o chrono.o

sort: chrono.o
	g++ -std=c++17 -Wall chrono.o sort_vs_paral_sort.cpp -o test_sort -ltbb

foreach: chrono.o
	g++ -std=c++17 -Wall chrono.o parallel_for_each.cpp -o foreach -ltbb

foreach_unseq: chrono.o
	g++ -std=c++17 -Wall chrono.o parallel_for_each_unseq.cpp -o foreach_unseq -ltbb

fill: chrono.o
	g++ -std=c++17 -Wall chrono.o parallel_fill.cpp -o fill -ltbb

run :
	./test_sort
	./foreach
	./foreach_unseq
	./fill

clean:
	rm -f *.o foreach test_sort foreach_unseq fill
