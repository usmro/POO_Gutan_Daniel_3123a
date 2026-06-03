CXX=g++
CXXFLAGS=-std=c++17 -Wall -Wextra -Iinclude
SRC=$(wildcard src/*.cpp)
SRC_NO_MAIN=$(filter-out src/main.cpp,$(SRC))
APP=spital
TEST_APP=tests_runner

all: $(APP)

$(APP): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(APP)

test: $(TEST_APP)
	./$(TEST_APP)

$(TEST_APP): $(SRC_NO_MAIN) tests/test_programari_facturi.cpp
	$(CXX) $(CXXFLAGS) $(SRC_NO_MAIN) tests/test_programari_facturi.cpp -o $(TEST_APP)

clean:
	rm -f $(APP) $(TEST_APP)

.PHONY: all test clean
