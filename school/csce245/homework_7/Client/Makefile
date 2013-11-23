TOP=..
include $(TOP)/Makefile.vars$(MKSUFFIX)
include Makefile.vars$(MKSUFFIX)

HDR=$(OFILES:.o=.h)
SRC=$(OFILES:.o=.C)

all:	$(TOP)/$(CLIENTNAME)
	@echo "Made in Client"

$(TOP)/$(CLIENTNAME):	$(OFILES)
	$(CXX) $(OFILES) -o $(TOP)/$(CLIENTNAME) $(LFLAGS) 

clean:	
	rm -f *.o core *~ a.out

distclean: clean
	rm -f $(TOP)/$(CLIENTNAME)

%.o:	%.C %.h $(ALLDEP) $(HDR)
	$(CXX) $(CFLAGS) $*.C -o $@

$(COMMONLIBDEP): FORCE
	@cd $(COMMONDIR); \
	make

.PHONY:	FORCE

