# project name (generate executable with this name)
TARGET   = QInterpreter

CC       = g++
INC_DIR = include
# compiling flags here
CFLAGS   =  -std=c++11 -I$(INC_DIR)

LINKER   = g++ -o
# linking flags here
LFLAGS   = 

# change these to set the proper directories where each files should be
SRCDIR   = src
GENDIR	 = $(SRCDIR)/gen
INCDIR   = include
OBJDIR   = obj
BINDIR   = bin

SOURCES  := $(wildcard $(SRCDIR)/*.cpp)
INCLUDES := $(wildcard $(INCDIR)/*.h)	
OBJECTS  := $(SOURCES:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
rm       = rm -f

$(BINDIR)/$(TARGET): $(OBJDIR)/expresiones.o $(OBJDIR)/lexico.o $(OBJECTS)
	@$(LINKER) $@ $(LFLAGS) $(OBJDIR)/expresiones.o $(OBJDIR)/lexico.o $(OBJECTS)
	@echo "Linking complete!"

$(OBJECTS): $(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "Compiled "$<" successfully!"

$(OBJDIR)/expresiones.o : $(GENDIR)/expresiones.c
	@$(CC) $(CFLAGS) -c -o $(OBJDIR)/expresiones.o $(GENDIR)/expresiones.c	

$(GENDIR)/expresiones.c : $(SRCDIR)/expresiones.y     
	bison -d -o $(GENDIR)/expresiones.c $(SRCDIR)/expresiones.y

$(OBJDIR)/lexico.o : $(GENDIR)/lex.yy.c		
	g++ -c -o $(OBJDIR)/lexico.o $(GENDIR)/lex.yy.c 

$(GENDIR)/lex.yy.c: $(SRCDIR)/lexico.l
	flex -o $(GENDIR)/lex.yy.c $(SRCDIR)/lexico.l

.PHONEY: clean
clean:
	@$(rm) $(OBJECTS) $(wildcard $(GENDIR)/*)
	@echo "Cleanup complete!"

.PHONEY: remove
remove: clean
	@$(rm) $(BINDIR)/$(TARGET)
	@echo "Executable removed!"
