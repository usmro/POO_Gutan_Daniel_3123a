CXX=g++
CXXFLAGS=-std=c++17 -Wall -Wextra -Iinclude
SRC=$(wildcard src/*.cpp)
SRC_NO_MAIN=$(filter-out src/main.cpp,$(SRC))
OBJ=$(SRC:.cpp=.o)
OBJ_NO_MAIN=$(SRC_NO_MAIN:.cpp=.o)
APP=spital
TEST_APP=tests_runner

all: $(APP)

$(APP): $(OBJ)
	$(CXX) $(OBJ) -o $(APP)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

test: $(TEST_APP)
	./$(TEST_APP)

$(TEST_APP): $(OBJ_NO_MAIN) tests/test_programari_facturi.cpp
	$(CXX) $(CXXFLAGS) $(OBJ_NO_MAIN) tests/test_programari_facturi.cpp -o $(TEST_APP)

run: $(APP)
	./$(APP)

clean:
	rm -f $(APP) $(TEST_APP) src/*.o

.PHONY: all test run clean
