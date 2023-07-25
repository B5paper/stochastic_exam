objs = parse_args.o display.o examine.o file_and_encoding.o main.o \
	materials_processing.o sample.o state.o tests.o system_info.o

main: $(objs)
	g++ -g $(objs) -o main

parse_args.o: parse_args.cpp
	g++ -g -c parse_args.cpp -o parse_args.o

display.o: display.cpp
	g++ -g -c display.cpp

examine.o: examine.cpp
	g++ -g -c examine.cpp -o examine.o

file_and_encoding.o: file_and_encoding.cpp
	g++ -g -c file_and_encoding.cpp -o file_and_encoding.o

main.o: main.cpp
	g++ -g -c main.cpp -o main.o

materials_processing.o: materials_processing.cpp
	g++ -g -c materials_processing.cpp -o materials_processing.o

sample.o: sample.cpp
	g++ -g -c sample.cpp -o sample.o

state.o: state.cpp
	g++ -g -c state.cpp -o state.o

tests.o: tests.cpp
	g++ -g -c tests.cpp -o tests.o

system_info.o: system_info.cpp
	g++ -g -c system_info.cpp -o system_info.o


clean:
	rm -f $(objs) main