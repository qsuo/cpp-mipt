CXX:= g++
CXXFLAGS:= -Wall -MD 
TEST_DIR:= ./tests
GTEST_DIR:= $(TEST_DIR)/gtest
GTEST_BUILD_DIR:= $(GTEST_DIR)/build
GTEST_INSTALL_DIR:= $(GTEST_DIR)/install

TEST_FLAGS:= -I$(GTEST_INSTALL_DIR)/include/ -L$(GTEST_INSTALL_DIR)/lib/
LIB_FLAGS:= -lgtest

TEST_SOURCES:= $(wildcard $(TEST_DIR)/*.cpp)
TEST_OBJS:= $(TEST_SOURCES:.cpp=.o)

SOURCES:= $(wildcard *.cpp)
OBJS:= $(SOURCES:.cpp=.o)

EXE:= test main

.PHONY: all clean

all: gtestlib $(EXE) 

-include *.d $(TEST_DIR)/*.d

gtestlib:
	@echo $(TEST_OBJS)
	@mkdir -p $(GTEST_BUILD_DIR) && cd $(GTEST_BUILD_DIR) && CXX=$(CXX) cmake -Dgtest_disable_pthreads=ON ../googletest/ && make
	@mkdir -p $(GTEST_INSTALL_DIR)
	@cp -r $(GTEST_DIR)/googletest/include $(GTEST_INSTALL_DIR)
	@cp -r $(GTEST_BUILD_DIR)/lib $(GTEST_INSTALL_DIR)

$(TEST_DIR)/%.o: $(TEST_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) $(TEST_FLAGS) -o $@ -c $< $(LIB_FLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -o $@ -c $<

test: $(TEST_OBJS) 
	$(CXX) $(CXXFLAGS) $(TEST_FLAGS) -o $@ $^	$(LIB_FLAGS)

main: $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

clean:
	rm -rf $(GTEST_BUILD_DIR) $(GTEST_INSTALL_DIR) $(EXE) $(OBJS) $(TEST_OBJS) *.d $(TEST_DIR)/*.d
