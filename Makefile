#define colors for nice output
ifneq (,$(findstring xterm,${TERM}))
	RED          := $(shell tput -Txterm setaf 1)
	GREEN        := $(shell tput -Txterm setaf 2)
	PURPLE       := $(shell tput -Txterm setaf 5)
	BLUE         := $(shell tput -Txterm setaf 6)
	RESET := $(shell tput -Txterm sgr0)
else
	RED       := ""
	GREEN		:= ""
	PURPLE       := ""
	BLUE         := ""
	RESET        := ""
endif


OUT=stage
CFLAGS=-Wall -I./include --std=c++11
CC=g++-11

FILES = Inverse_sensitivity main random Subsample_and_aggregate exponential_mechanism common_tools AboveThreshold myrtille comparaisons
CFILES = $(addsuffix .cpp, $(addprefix ./src/, $(FILES)))
OFILES = $(addsuffix .o, $(addprefix ./objects/, $(FILES)))
DIRECTORIES = ./objects ./proofs/temp


LATEXFLAGS=--shell-escape -synctex=1 -interaction=nonstopmode -file-line-error
LATEXFILES=myrtille_uniforme myrtille_exponentielle rapport myrtille_against_inverse_sensitivity_graph
LATEXFILES_tex=$(addsuffix .tex, $(addprefix ./proofs/source, $(LATEXFILES)))
LATEXFILES_pdf=$(addsuffix .pdf, $(addprefix ./proofs/, $(LATEXFILES)))

all: $(DIRECTORIES) $(OUT) latex

$(DIRECTORIES) :
	@echo "${GREEN}Creating missing directory" $@ "${RESET}"
	@mkdir $@

$(OUT): $(OFILES)
	@echo "${BLUE}Linking CXX objects${RESET}"
	@$(CC) -o $@ $^ $(LDFLAGS)
	@./stage

./objects/%.o: ./src/%.cpp | $(DIRECTORIES)
	@echo "${PURPLE}Building CXX object" $@ "${RESET}"
	@$(CC) $(CFLAGS) -o $@ -c $<

./proofs/rapport.pdf: ./proofs/source/rapport.tex
	@echo "${PURPLE}Compiling LaTeX files" $@ "${RESET}"
	@xelatex $(LATEXFLAGS) $< > /dev/null
	@echo "${PURPLE}Executing biber on rapport.aux${RESET}"
	@biber --fastsort ./rapport > /dev/null
	@echo "${PURPLE}Compiling LaTeX files" $@ "${RESET}"
	@xelatex $(LATEXFLAGS) $< > /dev/null
	@mv *.pdf ./proofs

./proofs/%.pdf: ./proofs/source/%.tex | $(DIRECTORIES)
	@echo "${PURPLE}Compiling LaTeX files" $@ "${RESET}"
	@xelatex $(LATEXFLAGS) $< > /dev/null
	@mv *.pdf ./proofs

latex: $(LATEXFILES_pdf)
	@$(MAKE) latex_move_temp_files

latex_move_temp_files: $(DIRECTORIES)
	@echo "${BLUE}Moving temporary files${RESET}"
#	find . -maxdepth 1 -name '*.bcf' -type f -print0 | xargs -0r mv ./proofs/temp/
ifneq (,$(wildcard ./*.bcf))
	@mv *.bcf ./proofs/temp/
endif
ifneq (,$(wildcard ./*.out))
	@mv *.out ./proofs/temp/
endif
ifneq (,$(wildcard ./*.synctex.gz))
	@mv *.synctex.gz ./proofs/temp/
endif
ifneq (,$(wildcard ./*.aux))
	@mv *.aux ./proofs/temp/
endif
ifneq (,$(wildcard ./*.log))
	@mv *.log ./proofs/temp/
endif
ifneq (,$(wildcard ./*.run.xml))
	@mv *.run.xml ./proofs/temp/
endif
ifneq (,$(wildcard ./proofs/source/*.aux))
	@mv ./proofs/source/*.aux ./proofs/temp/
endif
ifneq (,$(wildcard ./proofs/source/*.bbl))
	@mv ./proofs/source/*.bbl ./proofs/temp/
endif
ifneq (,$(wildcard ./proofs/source/*.blg))
	@mv ./proofs/source/*.blg ./proofs/temp/
endif

	
clean : latex_move_temp_files
	@echo "${RED}Cleaning${RESET}"
	@$(RM) $(OFILES)
	@$(RM) -dr $(DIRECTORIES)
	@$(RM) -dr ./_minted*

mrproper : clean
	@echo "${RED}Cleaning all files${RESET}"
	@$(RM) $(OUT)
	@$(RM) $(LATEXFILES_pdf)
