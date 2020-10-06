CXX:= g++

CXXFLAGS:= -Wall -MD 
TEST_DIR:= ./tests
GTEST_DIR:= ../googletest
GTEST_BUILD_DIR:= $(GTEST_DIR)/build
GTEST_INSTALL_DIR:= $(GTEST_DIR)/install

TEST_FLAGS:= -I$(GTEST_INSTALL_DIR)/include/ -L$(GTEST_INSTALL_DIR)/lib/
LIB_FLAGS:= -lgtest

TEST_SOURCES:= $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS:= $(TEST_SOURCES:.cpp=.o)

SOURCES:= $(wildcard *.cpp)
OBJS:= $(SOURCES:.cpp=.o)
OBJS := $(filter-out main.o, $(OBJS))

EXE:= test main
ALL:= $(EXE)

ifeq ($(wildcard $(GTEST_INSTALL_DIR)/*), )
	ALL:= gtestlib $(ALL)
endif

.PHONY: clean

all: $(ALL) 

-include *.d $(TEST_DIR)/*.d

gtestlib:
	@mkdir -p $(GTEST_BUILD_DIR) && cd $(GTEST_BUILD_DIR) && CXX=$(CXX) cmake -Dgtest_disable_pthreads=ON .. && make
	@mkdir -p $(GTEST_INSTALL_DIR)
	@cp -r $(GTEST_DIR)/googletest/include $(GTEST_INSTALL_DIR)
	@cp -r $(GTEST_BUILD_DIR)/lib $(GTEST_INSTALL_DIR)

$(TEST_DIR)/%.o: $(TEST_DIR)/%.cpp 
	$(CXX) $(CXXFLAGS) $(TEST_FLAGS) -o $@ -c $< $(LIB_FLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

test: $(TEST_OBJS) $(OBJS)
	$(CXX) $(CXXFLAGS) $(TEST_FLAGS) -o $@ $^ $(LIB_FLAGS)

main: main.o $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -rf $(EXE) $(OBJS) $(TEST_OBJS) *.d $(TEST_DIR)/*.d main.o

