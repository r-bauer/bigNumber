# makefile for big number calculator

IDIR=./include
SDIR=./src
CC=gcc
CFLAGS=-I$(IDIR)

ODIR=obj
LDIR=./lib

LIBS=-lm

_DEPS=	stackapp.h \
	stackdrv.h \
	stackgen.h \
	main.h \
	llgen.h \
	llapp.h \
	bn_app.h \
	bn_driver.h \
	utils.h
DEPS=$(addprefix $(IDIR)/, $(_DEPS))

_OBJ=	main.o \
	stackdrv.o \
	stackapp.o \
	stackgen.o \
	llgen.o \
	llapp.o \
	bn_app.o \
	bn_driver.o \
    utils.o

#OBJ=$(patsubst %, $(ODIR)/%, $(_OBJ))
OBJ=$(addprefix $(ODIR)/, $(_OBJ))

$(ODIR)/%.o: $(SDIR)/%.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

bignumber: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

# https://www.gnu.org/software/make/manual/make.html#Prerequisite-Types
all: $(OBJ)

$(OBJ): | $(ODIR)

$(ODIR):
	mkdir -p $(ODIR)

.PHONY:	clean

clean: 
	rm -fr $(ODIR) bignumber* *~ $(IDIR)/*~ $(SDIR)/*~

