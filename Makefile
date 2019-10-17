.DEFAULT_GOAL=run
.PHONY=all

#-----------------------------------------------#
#                                               #
#   			Compilation options   			#
#                                               #
#-----------------------------------------------#

# Compiler
CXX=g++

# Compiler flags
CXX_FLAGS=-lm -Wall

#-----------------------------------------------#
#                                               #
#       			Program options   			#
#                                               #
#-----------------------------------------------#

# Source file
PRG_SOURCE=source.gpp

#-----------------------------------------------#
#                                               #
#                    Recipes                    #
#                                               #
#-----------------------------------------------#

welcome: ## Show GalenaC++ beautiful welcome message
	@echo "┌────────────────────────────────────────┐"
	@echo "│                                        │"
	@echo "│               GalenaC++                │"
	@echo "│                                        │"
	@echo "├────────────────────────────────────────┤"
	@echo "│                                        │"
	@echo "│                    \\\\                  │"
	@echo "│                    (o>                 │"
	@echo "│                \\\\_//)                  │"
	@echo "│                 \\_/_)                  │"
	@echo "│                  _|_                   │"
	@echo "│                       v1.0.0           │"
	@echo "├────────────────────────────────────────┤"
	@echo "│ © Copyright 2019 - ARBACHE - MIQUET    │"
	@echo "└────────────────────────────────────────┘"
	@sleep 2

help: ## Show this help.
	@printf "\033[32m%-30s     \033[32m %s\n" "VARIABLE NAME" "DEFAULT_VALUE"
	@grep -E '^[a-zA-Z_-]+(\?=|=).*$$' $(MAKEFILE_LIST) |sort | awk 'BEGIN {FS = "(?=|=)"}; {printf "\033[36m%-30s     \033[0m %s\n", $$1, $$2}'
	@printf "\n\033[32m%-30s     \033[32m %s\033[0m\n" "RECIPE" "DESCRIPTION"
	@grep -E '^[a-zA-Z_-]+:.*?## .*$$' $(MAKEFILE_LIST) | sort | awk 'BEGIN {FS = ":.*?## "}; {printf "make \033[36m%-30s\033[0m %s\n", $$1, $$2}'

parser.tab.c: parser.y ## Build scanner
	@echo "Building parser..."
	@bison parser.y
	@echo "Done" && echo 

lex.yy.c: parser.tab.c scanner.l ## Build scanner
	@echo "Building scanner..."
	@flex scanner.l
	@echo "Done" && echo 

clean: ## Clean builded files
	@echo "Cleaning..."
	rm -rf parser.tab.c
	rm -rf lex.yy.c
	rm -rf program.exe
	rm -rf program
	@echo "Done" && echo 

program: build ## Build and fix program executable
	@[ -f "program.exe" ] && mv "program.exe" "program" || return 0

build: welcome parser.tab.c lex.yy.c ## Build the program
	@echo "Building program..."
	@echo "=============== G++ Output ==============="
	@$(CXX) lex.yy.c -o program $(CXX_FLAGS)
	@echo "=========================================="
	@echo "Done" && echo 

run: program ## Run the program
	./program $(PRG_SOURCE)