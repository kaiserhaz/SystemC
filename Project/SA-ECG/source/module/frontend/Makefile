TARGET_NAME:=$(TARGET)
TARGET_FILE:=$(TARGET_NAME).cpp

SRC_DIRS=.
BLD_DIR=build

SYSTEMC_HOME=/mnt/c/SystemC/systemc-2.3.4
SYSTEMC_AMS_HOME=/mnt/c/SystemC/systemc-ams-2.3.4

ARCH=linux64

CXX=g++
CXXFLAGS=-std=c++17 -Wall
CPPFLAGS=-I$(SYSTEMC_HOME)/include -I$(SYSTEMC_AMS_HOME)/include
LDFLAGS=-L$(SYSTEMC_HOME)/lib-$(ARCH) -L$(SYSTEMC_AMS_HOME)/lib-$(ARCH)
LDLIBS=-lsystemc -lsystemc-ams

help:
	@echo "Hello!"
	@echo "Use the following rules to make the programme:"
	@echo "	exe  : Makes the executable. Please provide the filename in TARGET var."
	@echo "	clean: cleans all the temp files."

clean:
	rm -rf build
	rm *.exe
	@echo "Done cleaning."

$(BLD_DIR)/$(TARGET_NAME).o: $(SRC_DIRS)/$(TARGET_FILE)
	@echo "###-----------------------###"
	@echo "### MAKING OBJ FILE FIRST ###"
	@echo "###-----------------------###"
	if [ ! -d "$(BLD_DIR)" ]; then \
		mkdir "$(BLD_DIR)";        \
	fi
	@echo "Running compiler."
	$(CXX) -c -v $(CPPFLAGS) $(CXXFLAGS) $^ -o $@

exe: $(BLD_DIR)/$(TARGET_NAME).o
	@echo "###-----------------------###"
	@echo "### MAKING EXE FILE NEXTT ###"
	@echo "###-----------------------###"
	@echo "Running linker."
	$(CXX) -v $^ -o $(TARGET_NAME).$@ $(LDFLAGS) $(LDLIBS)
 
.PHONY: clean exe
