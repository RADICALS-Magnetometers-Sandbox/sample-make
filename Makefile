ROOT = ${PWD}
BLDDIR = $(TOPDIR)/bld
BINDIR = $(TOPDIR)/bin

SUBDIRS = gen src

.PHONY: all $(SUBDIRS)
all: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ ROOT=$(ROOT) BINDIR=$(BINDIR) BLDDIR=$(BLDDIR)

.PHONY: clean
clean:
	for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir ROOT=$(ROOT) clean; \
	done


