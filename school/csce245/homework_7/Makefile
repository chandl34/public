# Top level makefile driver for The Game

# NOTES ON HOW TO USE THIS MAKE STUFF:
#
#  (1) In the top level directory, and in each of the subdirectories
#      Common/, Client/, Doc/ and Server/, there is a file called
#      'Makefile.vars'.
#  (2) Also in top-level directory Makefile.vars you'll find a
#      number of other variable definitions worth being aware of, like
#      CLIENTNAME and SERVERNAME, which will be the names the
#      corresponding programs are compiled into.
#  (4) In the Makefile.vars in EACH of the subdirectories, there is
#      an OFILES= variable definition.  Add all the .o's you'll you for
#      files in that subdirectory, like OFILES=foo.o bar.o bletch.o

# Main supported targets:
#
# make, make all
#       Bring Common/ Client/ Doc/ and Server/ up-to-date
#
# make clean
#       Clean in Common/ Client/ Doc/ and Server/
#
# make distclean
#       Distclean (remove .a + apps too) in Common/ Client/ Doc/ and Server/
#
# make distrib
#       Store tar file containing everything in ../
#

TOP=.
include Makefile.vars$(MKSUFFIX)  # Leave MKSUFFIX undefined/empty for normal usage..

# These targets are forwarded to all the SUBDIRS
TARGETS=all clean distclean test

# Source locations
#SUBDIRS=Common Client Server
SUBDIRS=Client Server

default: all

# Forwarding rule
$(TARGETS):
	@$(MAKE) TOP$@;\
	allstat=0;\
	for i in $(SUBDIRS);\
	do\
	  cd $$i;\
	  $(MAKE) $@;\
	  status=$$?;\
          if [ $$status -ne 0 ] ; then allstat=1; fi;\
          cd ..;\
        done;\
        exit $$allstat

TOPclean:
	rm -f *~ core *.log a.out

TOPall:

TOPtest:

TOPdistclean: TOPclean

distrib: distclean
	rm -f core
	rm -f Game*.tar.gz
	tar cvzf ../Game$(GAMEVERSION).tar.gz .

