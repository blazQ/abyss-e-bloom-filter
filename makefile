SRC_DIR := src
OBJ_DIR := obj
BIN_DIR := .

CXX=g++

EXE_DIST := $(BIN_DIR)/DistributionHash.out
EXE_BENCH := $(BIN_DIR)/BenchHash.out
EXE_BLOOM := $(BIN_DIR)/BloomTest.out
EXE_CBLOOM := $(BIN_DIR)/CBloomTest.out

SRC_DIST := $(wildcard $(SRC_DIR)/DistributionHash.cpp $(SRC_DIR)/MurmurHash3.cpp)
SRC_BENCH := $(wildcard $(SRC_DIR)/BenchHash.cpp $(SRC_DIR)/MurmurHash3.cpp)
SRC_BLOOM := $(wildcard $(SRC_DIR)/BloomTest.cpp)
SRC_CBLOOM := $(wildcard $(SRC_DIR)/CascadeBloomTest.cpp)


OBJ_DIST := $(SRC_DIST:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
OBJ_BENCH := $(SRC_BENCH:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
OBJ_BLOOM := $(SRC_BLOOM:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)
OBJ_CBLOOM := $(SRC_BLOOM:$(SRC_DIR)/%.cpp=$(OBJ_DIR)/%.o)

CPPFLAGS:= -Iinclude -MMD -MP
CXXFLAGS:= -Wall -Wextra -Wpedantic -std=c++17
LDFLAGS:=
LDLIBS:= -lnthash -lcityhash

.PHONY: all clean

all: $(EXE_DIST) $(EXE_BENCH) $(EXE_BLOOM) $(EXE_CBLOOM)

$(EXE_DIST): $(OBJ_DIST) | $(BIN_DIR)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(EXE_BLOOM): $(OBJ_BLOOM) | $(BIN_DIR)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(EXE_BENCH): $(OBJ_BENCH) | $(BIN_DIR)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(EXE_CBLOOM): $(OBJ_CBLOOM) | $(BIN_DIR)
	$(CXX) $(LDFLAGS) $^ $(LDLIBS) -o $@

$(BIN_DIR) $(OBJ_DIR):
	mkdir -p $@

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp | $(OBJ_DIR)
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -c $< -o $@

clean:
	@$(RM) -rv $(OBJ_DIR)

-include $(OBJ_DIST:.o=.d)
-include $(OBJ_BENCH:.o=.d)
