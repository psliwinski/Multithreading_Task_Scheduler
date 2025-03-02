CXX = g++
CXXFLAGS = -Wall -Wextra -std=c++11 -pthread

all: task_scheduler

task_scheduler: main.o task_scheduler.o
	$(CXX) $(CXXFLAGS) -o task_scheduler main.o task_scheduler.o

main.o: main.cpp task_scheduler.h
	$(CXX) $(CXXFLAGS) -c main.cpp

task_scheduler.o: task_scheduler.cpp task_scheduler.h
	$(CXX) $(CXXFLAGS) -c task_scheduler.cpp

clean:
	rm -f *.o task_scheduler
