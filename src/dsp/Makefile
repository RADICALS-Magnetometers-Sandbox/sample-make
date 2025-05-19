INC = $(ROOT)/inc

CXXFLAGS = -O3 -Wall

%.o : %.cpp
	$(CXX) -c $(CXXFLAGS) -I$(INC) $< -o $@

OBJ = dsp.o

all: libdsp.a

libdsp.a: $(OBJ)
	$(AR) $(ARFLAGS) $@ $(OBJ)

.PHONY : clean
clean:
	-rm libdsp.a $(OBJ)
