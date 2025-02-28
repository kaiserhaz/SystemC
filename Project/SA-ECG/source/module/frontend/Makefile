TARGET_NAME=$(TARGET)
AUX_NAME=$(AUX)

EXE_DEP=$(BLD_DIR)/$(TARGET_NAME).o $(AUX_NAME).aux

SRC_DIR=.
BLD_DIR=build

SYSTEMC_HOME=/mnt/c/SystemC/systemc-2.3.4
SYSTEMC_AMS_HOME=/mnt/c/SystemC/systemc-ams-2.3.4
OCTAVE_INCLUDE=/usr/include/octave-7.3.0
OCTAVE_LIB=/usr/lib/x86_64-linux-gnu/octave/7.3.0

ARCH=linux64

CXX=g++
CXXFLAGS=-std=c++17 -Wall
CPPFLAGS=-I$(SYSTEMC_HOME)/include -I$(SYSTEMC_AMS_HOME)/include -I$(OCTAVE_INCLUDE)
LDFLAGS=-L$(SYSTEMC_HOME)/lib-$(ARCH) -L$(SYSTEMC_AMS_HOME)/lib-$(ARCH) -L$(OCTAVE_LIB) -Wl,-rpath,$(shell octave-config -p OCTLIBDIR)
LDLIBS=-lsystemc -lsystemc-ams -loctinterp -loctave
OXX=mkoctfile
OXXFLAGS=--link-stand-alone

help:
	@echo "Hello!"
	@echo "Use the following rules to make the programme:"
	@echo "	exe TARGET=<target>  : makes the executable <target>.exe."
	@echo "	clean                : cleans all the temp files and build directory."
	@echo "Additional variables to define:"
	@echo " AUX=<aux>            : auxiliary files from other modules."
	@echo " AUX_DIR=<dir_path>   : auxiliary directory path."

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

%.aux: $(AUX_DIR)/%.cpp
	@echo "###-----------------------###"
	@echo "### MAKING AUX FILE FIRST ###"
	@echo "###-----------------------###"
ifneq (,$(wildcard $(AUX_DIR)/$(BLD_DIR)))
	$(MAKE) clean --directory $(AUX_DIR)
endif
	@echo "Making in auxiliary dir."
	$(MAKE) --directory $(AUX_DIR) $(BLD_DIR)/$(AUX_NAME).o
	cp $(AUX_DIR)/$(BLD_DIR)/$(AUX_NAME).o $(SRC_DIR)/$(BLD_DIR)/$(AUX_NAME).o
	$(MAKE) clean --directory $(AUX_DIR)

$(BLD_DIR)/%.o: $(SRC_DIR)/%.cpp
	@echo "###-----------------------###"
	@echo "### MAKING OBJ FILE FIRST ###"
	@echo "###-----------------------###"
ifeq (,$(wildcard $(BLD_DIR)))
	mkdir "$(BLD_DIR)";
endif
	@echo "Running compiler."
	$(CXX) -c -v $(CPPFLAGS) $(CXXFLAGS) $(MAKE_UPPER_CPPFLAGS) $^ -o $@

exe: $(EXE_DEP)
	@echo "###-----------------------###"
	@echo "### MAKING EXE FILE NEXTT ###"
	@echo "###-----------------------###"
	@echo "Running linker."
	$(CXX) -v $(patsubst %.aux, $(BLD_DIR)/%.o, $^) -o $(TARGET_NAME).$@ $(LDFLAGS) $(LDLIBS)
 
.PHONY: clean exe
