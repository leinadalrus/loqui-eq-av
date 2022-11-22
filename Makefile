.PHONY: all clean

# Define required environment variables
#------------------------------------------------------------------------------------------------
# Define target platform: PLATFORM_DESKTOP, PLATFORM_RPI, PLATFORM_DRM, PLATFORM_ANDROID, PLATFORM_WEB
PLATFORM              ?= PLATFORM_DESKTOP

# Define project variables
PROJECT_NAME          ?= Loqui
PROJECT_VERSION       ?= 0.1.0
PROJECT_BUILD_PATH    ?= .
#
# 'make'        build executable file 'main'
# 'make clean'  removes all .o and executable files
#

# define the C/C++ compiler to use
CC = g++

# define any compile-time flags
CPPFLAGS    := -std=cpp14 -02 -Wall -Wextra -g

# define library paths in addition to /usr/lib
#   if I wanted to include libraries not in /usr/lib I'd specify
#   their path using -Lpath, something like:
LDFLAGS = -L$(builddir)
# SDL2
SDL2_DEVEL_MINGW_PATHS = -I.\\SDL2-devel-2.24.1-mingw\\SDL2-2.24.1\\i686-w64-mingw32\\include

COMPILER_FLAGS_FOR_SDL2 = -w -Wl, -subsystem, windows

LINKER_FLAGS_FOR_SDL2 = -lmingw32 -lSDL2main -lSDL2

# define output directory
OUTPUT  := output

# define source directory
SRC     := src

# define include directory
INCLUDE := includes

# define lib directory
LIB     := lib

ifeq ($(OS),Windows_NT)
PROCESSOR   := $(PROJECT_NAME)_processor.exe
CONTROLLER  := $(PROJECT_NAME)_controller.exe
SOURCEDIRS  := $(SRC)
INCLUDEDIRS := $(INCLUDE)
LIBDIRS     := $(LIB)
FIXPATH = $(subst /,\,$1)
RM          := del /q /f
MD  := mkdir
else
PROCESSOR   := processor
CONTROLLER  := controller
SOURCEDIRS  := $(shell find $(SRC) -type d)
INCLUDEDIRS := $(shell find $(INCLUDE) -type d)
LIBDIRS     := $(shell find $(LIB) -type d)
FIXPATH = $1
RM = rm -f
MD  := mkdir -p
endif

# define any directories containing header files other than /usr/include
INCLUDES    := $(patsubst %,-I%, $(INCLUDEDIRS:%/=%))

# define the C libs
LIBS        := $(patsubst %,-L%, $(LIBDIRS:%/=%))

# define the C source files
SOURCES     := $(wildcard $(patsubst %,%/*.c, $(SOURCEDIRS)))

# define the CPP object files 
OBJECTS     := $(SOURCES:.cpp=.out)

#
# The following part of the makefile is generic; it can be used to 
# build any executable just by changing the definitions above and by
# deleting dependencies appended to the file from 'make depend'
#
BUILD_DEBUG ?= yes
OUTPUTPROCESSOR     := $(call FIXPATH,$(OUTPUT)/$(PROCESSOR))
OUTPUTCONTROLLER    := $(call FIXPATH,$(OUTPUT)/$(CONTROLLER))

all: $(SDL2_DEVEL_MINGW_PATHS) $(COMPILER_FLAGS_FOR_SDL2) $(LINKER_FLAGS_FOR_SDL2) $(LIBRARY_PATHS) $(COMPILER_FLAGS) $(LINKER_FLAGS) $(OUTPUT) $(PROCESSOR) $(CONTROLLER); @echo BUILD_DEBUG outputs as $(BUILD_DEBUG); @echo Executing 'all' complete!

$(OUTPUT):
    $(MD) $(OUTPUT)

$(PROCESSOR): $(OBJECTS) 
    $(CC) $(CPPFLAGS) $(INCLUDES) -o $(OUTPUTPROCESSOR) $(OBJECTS) $(LDFLAGS) $(LIBS)

$(CONTROLLER): $(OBJECTS) 
    $(CC) $(CPPFLAGS) $(INCLUDES) -o $(OUTPUTCONTROLLER) $(OBJECTS) $(LDFLAGS) $(LIBS)

# this is a suffix replacement rule for building .o's from .c's
# it uses automatic variables $<: the name of the prerequisite of
# the rule(a .c file) and $@: the name of the target of the rule (a .o file) 
# (see the gnu make manual section about automatic variables)
.cpp .o:
    $(CC) $(CPPFLAGS) $(INCLUDES) -c $<  -o $@

.PHONY: clean
clean: $(RM) $(OUTPUTMAIN); $(RM) $(call FIXPATH,$(OBJECTS)) ;@echo Cleanup complete!

run: all; ./$(OUTPUTPROCESSOR); ./$(OUTPUTCONTROLLER); @echo Executing 'run: all' complete!