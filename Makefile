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
CFLAGS=-Wall -I./include --std=c++20
CC=g++-11

FILES = Inverse_sensitivity main random Subsample_and_aggregate exponential_mechanism common_tools AboveThreshold myrtille comparaisons
CFILES = $(addsuffix .cpp, $(addprefix ./src/, $(FILES)))
OFILES = $(addsuffix .o, $(addprefix ./objects/, $(FILES)))
DIRECTORIES = ./objects ./proofs/temp


LATEXFLAGS=--shell-escape -interaction=nonstopmode -file-line-error
LATEXFILES= fig0 fig1 fig2 fig2_log_log fig3_1.000000 fig3_1.000000_log_log fig3_0.500000 fig4_1.000000 fig4_1.000000_log_log fig4_0.500000 fig5 fig6 rapport
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

./proofs/rapport.pdf: ./proofs/source/rapport.tex ./proofs/fig0.pdf ./proofs/fig1.pdf ./proofs/fig2.pdf ./proofs/fig2_log_log.pdf ./proofs/fig3_1.000000.pdf ./proofs/fig3_1.000000_log_log.pdf ./proofs/fig3_0.500000.pdf ./proofs/fig4_1.000000.pdf ./proofs/fig4_1.000000_log_log.pdf ./proofs/fig4_0.500000.pdf ./proofs/fig5.pdf ./proofs/fig6.pdf
	@echo "${PURPLE}Compiling LaTeX files" $@ "${RESET}"
	@xelatex $(LATEXFLAGS) $< > /dev/null
	@echo "${PURPLE}Executing biber on rapport.aux${RESET}"
	@biber ./rapport > /dev/null
	@echo "${PURPLE}Compiling LaTeX files" $@ "${RESET}"
	@xelatex $(LATEXFLAGS) $< > /dev/null
	@mv *.pdf ./proofs

	
./proofs/fig%.pdf: ./proofs/source/fig%.tex
	@echo "${PURPLE}Compiling LaTeX files" $@ "${RESET}"
	@xelatex $(LATEXFLAGS) $< > /dev/null
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
ifneq (,$(wildcard ./*.bbl))
	@mv *.bbl ./proofs/temp/
endif
ifneq (,$(wildcard ./*.blg))
	@mv *.blg ./proofs/temp/
endif
ifneq (,$(wildcard ./*.toc))
	@mv *.toc ./proofs/temp/
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
