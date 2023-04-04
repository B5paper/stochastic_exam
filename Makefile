main.exe:
	g++ file_and_encoding.cpp materials_processing.cpp main.cpp -o main.exe
clean:
	rm *.o *.exe