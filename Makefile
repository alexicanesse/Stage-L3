#define colors for nice output
ifneq (,$(findstring xterm,${TERM}))
	RED          := $(shell tput -Txterm setaf 1)
	PURPLE       := $(shell tput -Txterm setaf 5)
	BLUE         := $(shell tput -Txterm setaf 6)
	RESET := $(shell tput -Txterm sgr0)
else
	RED       := ""
	PURPLE       := ""
	BLUE         := ""
	RESET        := ""
endif


OUT=stage
CFLAGS=-Wall -I./include 
CC=g++-11

FILES = Inverse_sensitivity main random Subsample_and_aggregate exponential_mechanism
CFILES = $(addsuffix .cpp, $(addprefix ./src/, $(FILES)))
OFILES = $(addsuffix .o, $(addprefix ./objects/, $(FILES)))
DIRECTORIES = ./objects


all: $(OUT)

$(DIRECTORIES) :
	@echo "${PURPLE}Creating missing directory" $@ "${RESET}"
	@mkdir $@

$(OUT): $(OFILES)
	@echo "${BLUE}Linking C objects" $@ "${RESET}"
	@$(CC) -o $@ $^ $(LDFLAGS)

./objects/%.o: ./src/%.cpp $(DIRECTORIES)
	@echo "${PURPLE}Building C object" $@ "${RESET}"
	@$(CC) $(CFLAGS) -o $@ -c $<

clean :
	@echo "${RED}Cleaning${RESET}"
	@$(RM) $(OFILES)
	
mrproper : clean
	@echo "${RED}Cleaning all files${RESET}"
	@$(RM) $(OUT)
