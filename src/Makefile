
INC = $(ROOT)/inc

S_OBJ = scheduler.o udp_server.o
C_OBJ = udp_client.o
T_OBJ = main.o

SUBDIRS = dsp sys

LIBS = dsp/libdsp.a sys/libsys.a $(ROOT)/gen/libhal.a

.PHONY: all $(SUBDIRS)
all: hello scheduler udp_client $(SUBDIRS)

hello: $(T_OBJ) $(SUBDIRS)
	$(CXX) -o $@ $(T_OBJ) $(LIBS)

scheduler: $(S_OBJ)
	$(CXX) -o $@ $(S_OBJ)

udp_client: $(C_OBJ)
	$(CXX) -o $@ $(C_OBJ)

$(SUBDIRS):
	$(MAKE) -C $@ ROOT=$(ROOT)

main.o: main.cpp ../inc/dsp.h ../inc/hal.h
	$(CXX) $(CXXFLAGS) -c -I$(INC) -o $@ $<

scheduler.o: scheduler.cpp ../inc/scheduler.h ../inc/comm.h
	$(CXX) $(CXXFLAGS) -c -I$(INC) -o $@ $<

.PHONY: clean
clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir ROOT=$(ROOT) clean; \
	done
	-rm hello $(OBJ)
