TARGET_NAME:=surface_ecg
TARGET_FILE:=$(TARGET_NAME).cpp
AUX_NAME:=gen_ecg
AUX_FILE:=$(AUX_NAME).cpp

SRC_DIRS=.
BLD_DIR=build

#SYSTEMC_HOME=/mnt/c/SystemC/systemc-2.3.4
#SYSTEMC_AMS_HOME=/mnt/c/SystemC/systemc-ams-2.3.4
OCTAVE_INCLUDE=/usr/include/octave-7.3.0
OCTAVE_LIB=/usr/lib/x86_64-linux-gnu/octave/7.3.0

ARCH=linux64

CXX=g++
CXXFLAGS=-std=c++17 -Wall
CPPFLAGS=-I$(OCTAVE_INCLUDE)
LDFLAGS=-L$(OCTAVE_LIB) -Wl,-rpath,$(shell octave-config -p OCTLIBDIR)
LDLIBS=-loctinterp -loctave
OXX=mkoctfile
OXXFLAGS=--link-stand-alone

help:
	@echo "Hello!"
	@echo "Use the following rules to make the programme:"
	@echo "	exe   : Makes the executable."
	@echo "	clean : cleans all the temp files and build directory."

clean-build:
ifneq (,$(wildcard $(BLD_DIR)))
	rm -rf $(BLD_DIR)
endif

clean-exe:
ifneq (,$(wildcard *.exe))
	rm *.exe
endif

clean-run:
ifneq (,$(wildcard *.dat))
	rm *.dat
endif

clean: clean-build clean-exe clean-run
	@echo "Done cleaning."

$(BLD_DIR)/%.o: $(SRC_DIRS)/%.cpp
	@echo "###-----------------------###"
	@echo "### MAKING OBJ FILE FIRST ###"
	@echo "###-----------------------###"
	if [ ! -d "$(BLD_DIR)" ]; then \
		mkdir "$(BLD_DIR)";        \
	fi
	@echo "Running compiler."
	$(CXX) -c -v $(CPPFLAGS) $(CXXFLAGS) $^ -o $@

exe: $(BLD_DIR)/$(TARGET_NAME).o $(BLD_DIR)/$(AUX_NAME).o
	@echo "###-----------------------###"
	@echo "### MAKING EXE FILE NEXTT ###"
	@echo "###-----------------------###"
	@echo "Running linker."
	$(OXX) -v $^ -o $(TARGET_NAME).$@ $(OXXFLAGS) $(LDFLAGS) $(LDLIBS)
 
.PHONY: clean exe
