#----------------------------------------------------------------------------
# Description: Makefile to build analyzers
# Created:     Mon Jun 29 15:52:41 2015 by mkanalyzer.py
# Author:      Daniele Marconi
#----------------------------------------------------------------------------
ifndef ROOTSYS
$(error *** Please set up Root)
endif

name    := analyzer

# Sub-directories
srcdir	:= src
tmpdir	:= tmp
libdir	:= lib
incdir	:= include

$(shell mkdir -p tmp)
$(shell mkdir -p lib)

# Set this equal to the @ symbol to suppress display of instructions
# while make executes
ifdef verbose
AT 	:=
else
AT	:= @
endif

header  := $(incdir)/tnm.h
linkdef := $(incdir)/linkdef.h
cinthdr := $(tmpdir)/dictionary.h
cintsrc := $(tmpdir)/dictionary.cc
cintobj := $(tmpdir)/dictionary.o

# Get list of sources to be compiled into applications
appsrcs	:= $(wildcard *.cc)

# Construct list of applications
applications := $(appsrcs:.cc=)

# Construct names of object models from list of sources
appobjs	:= $(addprefix $(tmpdir)/,$(appsrcs:.cc=.o))

# Get list of sources to be made into shared libraries
cppsrcs	:= $(wildcard $(srcdir)/*.cpp)
cppobjs	:= $(subst $(srcdir)/,$(tmpdir)/,$(cppsrcs:.cpp=.o))

ccsrcs	:= $(wildcard $(srcdir)/*.cc) 
ccobjs	:= $(subst $(srcdir)/,$(tmpdir)/,$(ccsrcs:.cc=.o))
objects	:= $(cppobjs) $(ccobjs) $(cintobj)

sharedlib := $(libdir)/libtnm.so

# Display list of applications to be built
#say	:= $(shell echo -e "Apps: $(applications)" >& 2)
#say	:= $(shell echo -e "AppObjs: $(appobjs)" >& 2)
#say	:= $(shell echo -e "Objects: $(objects)" >& 2)
#$(error bye!) 

#-----------------------------------------------------------------------
# 	Define which compilers and linkers to use

# 	C++ Compiler/Linker
CXX	:= clang++
LINK	:= clang++
CINT	:= rootcint

# 	Define paths to be searched for C++ header files (#include ....)

CPPFLAGS:= -I. -I$(incdir) -I$(srcdir) $(shell root-config --cflags) 

# 	Define compiler flags to be used
#	-c		perform compilation step only 
#	-g		include debug information in the executable file
#	-O2		optimize
#	-ansi	require strict adherance to C++ standard
#	-Wall	warn if source uses any non-standard C++
#	-pipe	communicate via different stages of compilation
#			using pipes rather than temporary files

CXXFLAGS:= -c -g -O2 -ansi -Wall -pipe -fPIC -Wno-ignored-qualifiers

#	C++ Linker
#   set default path to shared library

LD	:= $(LINK) -Wl,-rpath,$(PWD)/$(libdir)

OS	:= $(shell uname -s)
ifeq ($(OS),Darwin)
    LDSHARED	:= $(LD) -dynamiclib
else
    LDSHARED	:= $(LD) -shared
endif

#	Linker flags

LDFLAGS := -g

# 	Libraries

LIBS	:=  $(shell root-config --libs) -L$(libdir) -lMinuit  -lMathMore -lMathCore


#	Rules
#	The structure of a rule is
#	target : source
#		command
#	The command makes a target from the source. 
#	$@ refers to the target
#	$< refers to the source

all:	$(sharedlib) $(applications) 

bin:	$(applications)

lib:	$(sharedlib)

# Syntax:
# list of targets : target pattern : source pattern


# Make applications depend on shared libraries to force the latter
# to be built first

$(applications)	: %	: $(tmpdir)/%.o  $(sharedlib)
	@echo "---> Linking $@"
	$(AT)$(LD) $(LDFLAGS) $< $(LIBS) -ltnm -o $@

$(sharedlib)	: $(objects)
	@echo "---> Linking `basename $@`"
	$(AT)$(LDSHARED) $(LDFLAGS) -fPIC $(objects) $(LIBS) -o $@

$(cppobjs)	: $(tmpdir)/%.o	: $(srcdir)/%.cpp
	@echo "---> Compiling `basename $<`" 
	$(AT)$(CXX) $(CXXFLAGS) $(CPPFLAGS)  $< -o $@ >& $*.FAILED
	$(AT)rm -rf $*.FAILED

$(ccobjs)	: $(tmpdir)/%.o	: $(srcdir)/%.cc
	@echo "---> Compiling `basename $<`" 
	$(AT)$(CXX) $(CXXFLAGS) $(CPPFLAGS)  $< -o $@ >& $*.FAILED
	$(AT)rm -rf $*.FAILED

$(appobjs)	: $(tmpdir)/%.o	: %.cc
	@echo "---> Compiling `basename $<`" 
	$(AT)$(CXX) $(CXXFLAGS) $(CPPFLAGS)  $< -o $@ >& $*.FAILED
	$(AT)rm -rf $*.FAILED

$(cintobj)  : $(cintsrc)
	@echo "---> Compiling `basename $<`"
	$(AT)$(CXX) $(CXXFLAGS) $(CPPFLAGS) -c $< -o $@

$(cintsrc)  : $(header) $(linkdef)
	@echo "---> Generating dictionary `basename $@`"
	$(AT)$(CINT) -f $@ -c -I. -Iinclude -I$(ROOTSYS)/include $+


# 	Define clean up rules
clean   :
	rm -rf $(tmpdir)/*.o $(applications) $(libdir)/*.so
