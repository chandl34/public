TOP=..
include $(TOP)/Makefile.vars$(MKSUFFIX)
include Makefile.vars$(MKSUFFIX)

HDR=$(OFILES:.o=.h)
SRC=$(OFILES:.o=.C)

all:	$(COMMONLIBDEP)
	@echo "Made in common"

$(COMMONLIBDEP):	$(OFILES) $(ALLDEP)
	ar crv $(COMMONLIBDEP) $(OFILES)
	ranlib $(COMMONLIBDEP)

clean:
	rm -f *.o core *~ a.out

distclean: clean
	rm -f *.a

%.o:	%.C %.h $(ALLDEP) $(HDR)
	$(CXX) $(CFLAGS) $*.C -o $@

