all:
	g++ -std=c++17 -Wall sort_vs_paral_sort.cpp -o test_sort -ltbb
	./test_sort