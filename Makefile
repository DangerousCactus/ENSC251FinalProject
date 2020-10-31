#compile and link the application
all: main

#run the application
run: main
	./main

#link main.o and student.o to executable main
main: main.o student.o internationalStudent.o domesticStudent.o TOEFLScore.o
	g++ -g -o main main.o student.o internationalStudent.o domesticStudent.o TOEFLScore.o

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

#remove built files
clean:
	rm -rf build main *.o *~

#Zip the files (for GitHub CI)
zip:
	mkdir finalProject && cp -f ./*.* Makefile finalProject/ && zip -r finalProject.zip finalProject && rm -rf finalProject/

#Test using gtest and CMaKE
gtest:
	cmake --no-warn-unused-cli -DCMAKE_EXPORT_COMPILE_COMMANDS:BOOL=TRUE -DCMAKE_BUILD_TYPE:STRING=Debug -H/root/ENSC252/finalProject -B/root/ENSC252/finalProject/build -G "Unix Makefiles" &&\
	cmake --build build/ --config Debug --target all -- -j 10 &&\
	cmake --build build/ --config Debug --target all -- -j 10

tests:
	build/test/tests