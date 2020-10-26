
CXX:= g++
CXXFLAGS:= -Wall -MD -g
SRC_DIR:= ./src
TEST_DIR:= ./tests
GTEST_DIR:= ../googletest
GTEST_BUILD_DIR:= $(GTEST_DIR)/build
GTEST_INSTALL_DIR:= $(GTEST_DIR)/install

TEST_FLAGS:= -I$(GTEST_INSTALL_DIR)/include/ -I$(SRC_DIR) -L$(GTEST_INSTALL_DIR)/lib/
LIB_FLAGS:= -lgtest

TEST_SOURCES:= $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS:= $(TEST_SOURCES:.cpp=.o)

SOURCES:= $(wildcard $(SRC_DIR)/*.cpp)
OBJS:= $(SOURCES:.cpp=.o)
TEST_OBJS := $(filter-out $(SRC_DIR)/main.o, $(OBJS)) $(TEST_OBJS)

EXE:= test main
ALL:= $(EXE)

ifeq ($(wildcard $(GTEST_INSTALL_DIR)/*), )
	ALL:= gtestlib $(ALL)
endif

.PHONY: clean clean-all

all: $(ALL) 

-include $(SRC_DIR)/*.d $(TEST_DIR)/*.d

gtestlib:
	@mkdir -p $(GTEST_BUILD_DIR) && cd $(GTEST_BUILD_DIR) && CXX=$(CXX) cmake -Dgtest_disable_pthreads=ON .. && make
	@mkdir -p $(GTEST_INSTALL_DIR)
	@cp -r $(GTEST_DIR)/googletest/include $(GTEST_INSTALL_DIR)
	@cp -r $(GTEST_BUILD_DIR)/lib $(GTEST_INSTALL_DIR)

$(TEST_DIR)/%.o: $(TEST_DIR)/%.cpp 
	$(CXX) $(CXXFLAGS) $(TEST_FLAGS) -o $@ -c $< $(LIB_FLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

test: $(TEST_OBJS)
	$(CXX) $(CXXFLAGS) $(TEST_FLAGS) -o $@ $^ $(LIB_FLAGS)

main: $(SRC_DIR)/main.o $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -rf $(EXE) $(OBJS) $(TEST_OBJS) $(SRC_DIR)/*.d $(TEST_DIR)/*.d main.o

clean-all: clean
	rm -rf $(GTEST_INSTALL_DIR) $(GTEST_BUILD_DIR)
	


