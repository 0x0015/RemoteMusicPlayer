all:
	#g++ -coverage -c -std=c++11 -g -MMD -MP -MF main.o.d -o main.o main.cpp
	g++ main.cpp -o main -std=c++11 -g  libhttpserver/src/libhttpserver/dist/Debug/GNU-Linux-x86/libhttpserver.a -lboost_filesystem -lboost_date_time -lboost_chrono -lboost_regex -lboost_system -lpthread -lz -lboost_thread -lrt bass/x64/libbass.so --coverage
clean:
	rm -f main
	rm -f main.gcno
	rm -f main.gcda
