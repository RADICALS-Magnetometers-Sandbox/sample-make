INC = $(ROOT)/inc

CXXFLAGS = -O3 -Wall

%.o : %.cpp
	$(CXX) -c $(CXXFLAGS) -I$(INC) $< -o $@

OBJ = system.o

all: libsys.a

libsys.a: $(OBJ)
	$(AR) $(ARFLAGS) $@ $(OBJ)

.PHONY : clean
clean:
	-rm libsys.a $(OBJ)
