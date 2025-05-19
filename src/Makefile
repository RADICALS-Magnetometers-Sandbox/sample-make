
INC = $(ROOT)/inc

OBJ = main.o

SUBDIRS = dsp sys

LIBS = dsp/libdsp.a sys/libsys.a $(ROOT)/gen/libhal.a

.PHONY: all $(SUBDIRS)
all: hello $(SUBDIRS)

hello: $(OBJ) $(SUBDIRS)
	$(CXX) -o $@ $(OBJ) $(LIBS)

$(SUBDIRS):
	$(MAKE) -C $@ ROOT=$(ROOT)

main.o: main.cpp ../inc/dsp.h ../inc/hal.h
	$(CXX) $(CXXFLAGS) -c -I$(INC) -o $@ $<

.PHONY: clean
clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir ROOT=$(ROOT) clean; \
	done
	-rm hello $(OBJ)
