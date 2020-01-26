CXX = clang++
CXXFLAGS = -Wall
DEBUG = -g -DDEBUG
SRC = ./src
BIN = ./bin


all: BIN TMA4Question1 TMA4Question2 TMA4Question3

debug: BIN TMA4Question1_debug TMA4Question2_debug

BIN: 
	mkdir bin



TMA4Question1: $(SRC)/TMA4Question1.cpp
	$(CXX) $(CXXFLAGS) $< -o $(BIN)/$@

TMA4Question2: $(SRC)/TMA4Question2.cpp
	$(CXX) $(CXXFLAGS) $< -o $(BIN)/$@

TMA4Question3: $(SRC)/TMA4Question3.cpp
	$(CXX) $(CXXFLAGS) $< -o $(BIN)/$@




TMA4Question1_debug: $(SRC)/TMA4Question1.cpp
	$(CXX) $(CXXFLAGS) $(DEBUG) $< -o $(BIN)/$@

TMA4Question2_debug: $(SRC)/TMA4Question2.cpp
	$(CXX) $(CXXFLAGS) $(DEBUG) $< -o $(BIN)/$@

TMA4Question3_debug: $(SRC)/TMA4Question3.cpp
	$(CXX) $(CXXFLAGS) $(DEBUG) $< -o $(BIN)/$@



clean:
	rm -rf $(BIN)