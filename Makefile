#compile and link the application
all: main

#run the application
run: main
	./main

#link main.o and student.o to executable main
main: main.o student.o internationalStudent.o domesticStudent.o TOEFLScore.o StudentList.o
	g++ -g -o main main.o student.o internationalStudent.o domesticStudent.o TOEFLScore.o StudentList.o

#compile the main.cpp to main.o
main.o: main.cpp
	g++ -g -c main.cpp

#compile the student.cpp to student.o
student.o: student.cpp
	g++ -g -c student.cpp

#compile the internationalStudent.cpp to internationalStudent.o
internationalStudent.o: student.cpp
	g++ -g -c internationalStudent.cpp

#compile the domesticStudent.cpp to domesticStudent.o
domesticStudent.o: student.cpp
	g++ -g -c domesticStudent.cpp

#compile the TOEFLScore.cpp to TOEFLScore.o
TOEFLScore.o: student.cpp
	g++ -g -c TOEFLScore.cpp

#compile the StudentList.cpp to StudentList.o
StudentList.o: StudentList.cpp
	g++ -g -c StudentList.cpp

#remove built files
clean:
	rm -rf main *.o *~

#GitHub CI functions below
#install gtest
gtest:
	sudo apt-get install libgtest-dev && cd /usr/src/gtest && sudo cmake CMakeLists.txt && sudo make && sudo cp *.a /usr/lib &&\
	sudo ln -s /usr/lib/libgtest.a /usr/local/lib/libgtest.a && sudo ln -s /usr/lib/libgtest_main.a /usr/local/lib/libgtest_main.a
	
#make the tests and run them
runtest:
	cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Debug -B build/ -G "Unix Makefiles" &&\
	cmake --build build/ --config Debug --target all -- -j 10 &&\
	cd build/test && ./tests