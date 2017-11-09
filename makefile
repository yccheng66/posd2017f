CXX = g++
CXXFLAGS = -std=gnu++0x
LDFLAGS =
LIBS = -lgtest -lpthread
 
SRC_DIR = source
INCLUDE_DIR = include
TEST_DIR = utest
BUILD_DIR = build
TEST_TARGET = main

# use wildcard to get a list of all header files in (INCLUDE_DIR) folder
HEADERS=$(wildcard $(INCLUDE_DIR)/*.h)
# change the list of header files to object files, ex: include/atom.h -> build/atom.o
OBJECTS=$(patsubst $(INCLUDE_DIR)/%.h, $(BUILD_DIR)/%.o, $(HEADERS))
# get a list of test files in (TEST_DIR) folder
TEST_HEADERS = $(wildcard $(TEST_DIR)/*.h)
 
HEADER_TEMPLATE="\#ifndef %s\n\#define %s\n\n\n\nclass %s\n{\n    public:\n        %s();\n\n    private:\n\n};\n\n\#endif\n"
SOURCE_TEMPLATE="\#include \"../%s/%s\"\n\n\n\n%s::%s() {};\n"
TEST_HEADER_TEMPLATE="\#ifndef %s\n\#define %s\n\n\#include \"../%s/%s\"\n\nTEST(%s, example) {\n    EXPECT_TRUE(true);\n    EXPECT_FALSE(false);\n    EXPECT_EQ(true, true);\n}\n\n\#endif\n"
 
 
# $(BUILD_DIR)/$(TEST_TARGET).o $(OBJECTS)
# build/main.o build/atom.o
all: $(BUILD_DIR)/$(TEST_TARGET).o $(OBJECTS)
	@$(CXX) -o $(BUILD_DIR)/$(TEST_TARGET) $(BUILD_DIR)/$(TEST_TARGET).o $(OBJECTS) $(LDFLAGS) $(LIBS)

# $(BUILD_DIR)/$(TEST_TARGET).o
# build/main.o
$(BUILD_DIR)/$(TEST_TARGET).o: $(SRC_DIR)/$(TEST_TARGET).cpp $(TEST_HEADERS)
	@$(CXX) $(CXXFLAGS) -c $(SRC_DIR)/$(TEST_TARGET).cpp -o $(BUILD_DIR)/$(TEST_TARGET).o

# $(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(INCLUDE_DIR)/%.h
# build/atom.o: source/atom.cpp include/atom.h
# $< is the first prerequisite, $@ is the name of the file being generated
# following the example $< is source/atom.cpp and $@ is build/atom.o
$(BUILD_DIR)/%.o: $(SRC_DIR)/%.cpp $(INCLUDE_DIR)/%.h
	@$(CXX) $(CXXFLAGS) -c $< -o $@

# $(RM) = rm -f
clean:
	@$(RM) $(BUILD_DIR)/*
 
test: clean all
	@$(BUILD_DIR)/$(TEST_TARGET)
 
	
# $(subst <from>,<to>,<text>) replace <from> to <to> in <text>
# $(subst ., ,test.scanner) -> test scanner
# $(word <n>,<text>) get the nth word from text
# $(word 2,text scanner) -> scanner
test.%: clean all
	@$(BUILD_DIR)/$(TEST_TARGET) --gtest_filter=$(word 2,$(subst ., ,$@)).*
 

addClass.%:
	$(eval className=$(or $(word 2,$(subst ., ,$@)),$(value 2)))
	$(eval lowerCaseClassName=$(shell echo $(className) | tr A-Z a-z))
	$(eval upperCaseClassName=$(shell echo $(className) | tr a-z A-Z))
	$(eval headerFileName=$(lowerCaseClassName).h)
	$(eval sourceFileName=$(lowerCaseClassName).cpp)
	$(eval headerFileIncludeGuardName=$(upperCaseClassName)_H)
   
	@printf $(HEADER_TEMPLATE) $(headerFileIncludeGuardName) $(headerFileIncludeGuardName) $(className) $(className) > $(INCLUDE_DIR)/$(headerFileName)
	@printf $(SOURCE_TEMPLATE) $(INCLUDE_DIR) $(headerFileName) $(className) $(className) > $(SRC_DIR)/$(sourceFileName)
   
addClassWithTest.%: addClass.%
	$(eval testHeaderFileName=ut$(className).h)
	$(eval teatHeaderFileIncludeGuardName=UT$(upperCaseClassName)_H)
	@printf $(TEST_HEADER_TEMPLATE)  $(teatHeaderFileIncludeGuardName) $(teatHeaderFileIncludeGuardName)  $(INCLUDE_DIR) $(headerFileName) $(className) >$(TEST_DIR)/$(testHeaderFileName)
	@sed -i '\/\/ test header above/i \#include "../$(TEST_DIR)/$(testHeaderFileName)"' $(SRC_DIR)/$(TEST_TARGET).cpp