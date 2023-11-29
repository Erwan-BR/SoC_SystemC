# makefile
###############################################################
# Auteurs : Erwan BROUDIN, Adrien MILLASSEAU
# Objectif : Construire l'executable du gradient avec seuil
#################################################################
MODULE = seuil
SRCS = sc_main.cpp sc_seuil.cpp
OBJS = $(addprefix build/,$(SRCS:.cpp=.o))

# Liste des fichiers sources dans le dossier global
GLOBAL_SRCS = ../global/gdr.cpp ../global/sc_image.cpp
GLOBAL_OBJS = $(addprefix build/global/,$(notdir $(GLOBAL_SRCS:.cpp=.o)))

##########################################################################
TARGET_ARCH = linux64

CC = g++
OPT    = -O3 -Wno-deprecated
CPPFLAGS = -fpermissive -std=gnu++11 #-Wall -Wextra
CFLAGS = $(OPT) -fexceptions

INCDIR = -I. -I.. -I$(SYSTEMC)/include -I../global
LIBDIR = -L. -L.. -L$(SYSTEMC)/lib-linux64

LIBS   =  -lsystemc -lm

EXE    = bin/$(MODULE).x

.SUFFIXES: .cpp .o .x

$(EXE): $(OBJS) $(GLOBAL_OBJS) $(SYSTEMC)/lib-linux64/libsystemc.a 
	$(CC) $(CFLAGS) $(CPPFLAGS) $(INCDIR) $(LIBDIR) -o $@ $(OBJS) $(GLOBAL_OBJS) $(LIBS)

build/%.o: %.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(INCDIR) -c $< -o $@

# Règle de compilation pour les fichiers dans le dossier global
build/global/%.o: ../global/%.cpp
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CPPFLAGS) $(INCDIR) -c $< -o $@

clean:
	rm -rf build/* $(wildcard *~) bin/*