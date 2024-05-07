TARGET_FILE=vga_controller main
TARGET_NAME=vga_sim

SRC_DIRS=source
BLD_DIR=build

SYSTEMC_HOME=/mnt/c/SystemC/systemc-2.3.4
SYSTEMC_AMS_HOME=/mnt/c/SystemC/systemc-ams-2.3.4
OPENCV_HOME=/usr/local/include/opencv4

ARCH=linux64

OPENCV_LIBS = core highgui calib3d dnn features2d flann gapi imgcodecs imgproc ml objdetect photo video videoio stitching 

CXX=g++
CXXFLAGS=-std=c++17 -Wall
CPPFLAGS=-I$(SYSTEMC_HOME)/include -I$(SYSTEMC_AMS_HOME)/include -I$(OPENCV_HOME)
#CPPFLAGS+= -D_PRINT_DBG_=1
#CPPFLAGS+= -D_TRACE_DBG_=1
LDFLAGS=-L$(SYSTEMC_HOME)/lib-$(ARCH) -L$(SYSTEMC_AMS_HOME)/lib-$(ARCH) -L/usr/local/lib
LDLIBS=$(addprefix -lopencv_, $(OPENCV_LIBS)) -lsystemc-ams -lsystemc

help:
	@echo "Hello!"
	@echo "Use the following rules to make the programme:"
	@echo "	exe  : Makes the executable."
	@echo "	clean: cleans all the temp files."

clean:
	rm -rf build
	if [ -f $(TARGET_NAME).exe ]; then \
		rm $(TARGET_NAME).exe;         \
	fi
	@echo "Done cleaning."

%.o:
	@echo "###-----------------------###"
	@echo "### MAKING $@ "
	@echo "###-----------------------###"
	if [ ! -d $(BLD_DIR) ]; then \
		mkdir $(BLD_DIR);      \
	fi
	$(CXX) -c -v $(CPPFLAGS) $(CXXFLAGS) $(SRC_DIRS)/$(@:%.o=%.cpp) -o $(BLD_DIR)/$@


exe: $(addsuffix .o, $(TARGET_FILE))
	@echo "###-----------------------###"
	@echo "### MAKING EXE FILE NEXTT ###"
	@echo "###-----------------------###"
	$(CXX) -v -o $(TARGET_NAME).$@ $(foreach obj, $^, $(BLD_DIR)/$(obj)) $(LDFLAGS) $(LDLIBS)
