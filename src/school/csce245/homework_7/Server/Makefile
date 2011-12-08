TOP=..
include $(TOP)/Makefile.vars$(MKSUFFIX)
include Makefile.vars$(MKSUFFIX)

all:	$(TOP)/$(SERVERNAME)
	@echo "Made in Server"

HDR=$(OFILES:.o=.h)
SRC=$(OFILES:.o=.C)

$(TOP)/$(SERVERNAME):	$(OFILES) $(COMMONLIBDEP)
	$(CXX) $(OFILES) -o $(TOP)/$(SERVERNAME) $(LFLAGS) 

clean:	
	rm -f *.o core *~ a.out

distclean:	clean
	rm -f $(TOP)/$(SERVERNAME)

%.o:	%.C %.h $(ALLDEP) $(HDR)
	$(CXX) $(CFLAGS) $*.C -o $@

$(COMMONLIBDEP): FORCE
	@cd $(COMMONDIR); \
	make

.PHONY:	FORCE

