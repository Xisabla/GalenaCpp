.DEFAULT_GOAL=run
.PHONY=all

#
# ─── COMPILATION OPTIONS ────────────────────────────────────────────────────────
#

# Compiler
CXX=g++

# Compiler flags
CXX_FLAGS=-std=c++11

#
# ─── PROJECT SOURCES ────────────────────────────────────────────────────────────
#	

# Source files
SOURCES=$(shell find ./src -type f -name "*.cpp")

# Headers files
HEADERS=$(shell find ./src -type f -name "*.h")

# Objects files
OBJECTS=$(patsubst ./src/%.cpp, ./build/%.o, $(SOURCES))

# Spikes sources
SPIKES=$(shell find ./spikes -type f -name "*.cpp")

#
# ─── PROGRAM OPTIONS ────────────────────────────────────────────────────────────
#

# Source file
PGR_SOURCE=source.gpp


WELCOME_MSG=" ┌────────────────────────────────────────┐\n\
│                                        │\n\
│          GalenaC++ Building            │\n\
│                                        │\n\
├────────────────────────────────────────┤\n\
│                                        │\n\
│                    \\\\\                  │\n\
│                    (o>                 │\n\
│                \\\\\_//)                  │\n\
│                 \\_/_)                  │\n\
│                  _|_                   │\n\
│                       v1.0.0           │\n\
├────────────────────────────────────────┤\n\
│ © Copyright 2019 - ARBACHE - MIQUET    │\n\
└────────────────────────────────────────┘"

#
# ─── REPICES ────────────────────────────────────────────────────────────────────
#

.depend:
	@$(CXX) -E -MM $(SOURCES) > .depend

welcome: ## Show GalenaC++ beautiful welcome message
	@echo $(WELCOME_MSG)

help: ## Show this help.
	@printf "\033[32m%-30s     \033[32m %s\n" "VARIABLE NAME" "DEFAULT_VALUE"
	@grep -E '^[a-zA-Z_-]+(\?=|=).*$$' $(MAKEFILE_LIST) |sort | awk 'BEGIN {FS = "(?=|=)"}; {printf "\033[36m%-30s     \033[0m %s\n", $$1, $$2}'
	@printf "\n\033[32m%-30s     \033[32m %s\033[0m\n" "RECIPE" "DESCRIPTION"
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "make \033[36m%-30s\033[0m %s\n", $$1, $$2}'

clean: ## Clean builded files
	@echo "Cleaning..."
	rm -rf .depend
	rm -rf build
	rm -rf parser.tab.c
	rm -rf lex.yy.c
	rm -rf program.exe
	rm -rf program
	@echo "Done" && echo 

build/%.o: src/%.cpp src/%.h .depend ## Build object files
	@mkdir -p build
	$(CXX) $(CXX_FLAGS) -g -c $< -o $@

parser.tab.c: parser.y ## Build scanner
	@echo "Building parser..."
	bison parser.y
	@echo "Done" && echo 

lex.yy.c: parser.tab.c scanner.l ## Build scanner
	@echo "Building scanner..."
	flex scanner.l
	@echo "Done" && echo 

build: welcome parser.tab.c lex.yy.c $(OBJECTS) ## Build the program
	@echo "Building program..."
	@echo "=============== G++ Output ==============="
	$(CXX) lex.yy.c $(OBJECTS) -o program $(CXX_FLAGS)
	@echo "=========================================="
	@echo "Done" && echo 

program: build ## Build and fix program executable
	@[ -f "program.exe" ] && mv "program.exe" "program" || return 0

run: program ## Run the program
	./program $(PGR_SOURCE)

#
# ─── SPIKES ─────────────────────────────────────────────────────────────────────
#

build/s_%: spikes/%.cpp build/%.o ## Common spike building
	$(CXX) $(CXX_FLAGS) $^ -o $@

build/s_VarManager: spikes/VarManager.cpp build/VarManager.o build/Memory.o
	$(CXX) $(CXX_FLAGS) $^ -o $@
	
spike/%: build/s_% ## Common spike running
	@echo "=========================================="
	@echo " START SPIKE: $@"
	@echo "=========================================="
	@./$<
	@echo "=========================================="
	@echo " END SPIKE: $@"
	@echo "=========================================="

spikes: $(patsubst ./spikes/%.cpp, ./spike/%, $(SPIKES)) ## Run all spikes