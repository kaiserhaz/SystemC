TARGET_FILE=bench.cpp
TARGET_NAME=saecg

SRC_DIRS=source
BLD_DIR=build

SYSTEMC_HOME=/mnt/c/SystemC/systemc-2.3.4
SYSTEMC_AMS_HOME=/mnt/c/SystemC/systemc-ams-2.3.4

ARCH=linux64

CXX=g++
CXXFLAGS=-std=c++17 -Wall
CPPFLAGS=-I$(SYSTEMC_HOME)/include
LDFLAGS=-L$(SYSTEMC_HOME)/lib-$(ARCH)
LDLIBS=-lsystemc

help:
	@echo "Hello!"
	@echo "Use the following rules to make the programme:"
	@echo "	exe  : Makes the executable."
	@echo "	clean: cleans all the temp files."

clean:
	rm -rf build
	rm $(TARGET_NAME).exe
	@echo "Done cleaning."

$(BLD_DIR)/$(TARGET_NAME).o: $(SRC_DIRS)/$(TARGET_FILE)
	@echo "###-----------------------###"
	@echo "### MAKING OBJ FILE FIRST ###"
	@echo "###-----------------------###"
	if [ ! -d "$(BLD_DIR)" ]; then \
		mkdir "$(BLD_DIR)";        \
	fi 
	$(CXX) -c -v $(CPPFLAGS) $(CXXFLAGS) $^ -o $@

exe: $(BLD_DIR)/$(TARGET_NAME).o
	@echo "###-----------------------###"
	@echo "### MAKING EXE FILE NEXTT ###"
	@echo "###-----------------------###"
	$(CXX) -v $^ -o $(TARGET_NAME).$@ $(LDFLAGS) $(LDLIBS)
