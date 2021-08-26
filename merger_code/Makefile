#all:
#	g++ main.cpp -v -o test -lpthread -lcrypto -lssl -lpaho-mqtt3as -lpaho-mqttpp3
#clean:
#	rm *.cpp.*

NAME_MODULE	= app
# CXX			= g++
# CC			= gcc
CXX				= gcc
OBJ_DIR		= build_$(NAME_MODULE)

OPTIMIZE_OPTION	=	-g -O3
WARNNING_OPTION	+=	#-Werror -Wno-missing-field-initializers -W

-include aes/Makefile.mk
-include cJson/Makefile.mk
-include app/Makefile.mk

CXXFLAGS	+= -I/usr/local/include
CXXFLAGS	+= -I/usr/include
CXXFLAGS    += -I../..

# CXX compiler option
CXXFLAGS	+=	$(OPTIMIZE_OPTION)	\
		$(WARNNING_OPTION)	\
		-Wall			\
		-Winline		\
		-pipe			\
		-g			\

# Library paths
LDFLAGS	+= -L/usr/local/lib
LDFLAGS	+= -L/usr/include
LDFLAGS	+= -Wl,-Map=$(OBJ_DIR)/$(NAME_MODULE).map

#Library libs
LDLIBS	+=	-lpthread		\
		-lrt			\
		-lm			\
		-lcrypto \
		-lssl \

all: create $(OBJ_DIR)/$(NAME_MODULE)

create:
	@echo mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c
	@echo CXX $<
	@$(CXX) -c -o $@ $< $(CXXFLAGS) $(LDFLAGS) $(LDLIBS)

$(OBJ_DIR)/$(NAME_MODULE): $(OBJ)
	@echo ---------- START LINK PROJECT ----------
	@echo $(CXX) -o $@ $^ $(CXXFLAGS)
	@$(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS) $(LDLIBS)

.PHONY: debug
debug:
	sudo gdb $(OBJ_DIR)/$(NAME_MODULE)

.PHONY: run
run:
	sudo ./$(OBJ_DIR)/$(NAME_MODULE)

.PHONY: clean
clean:
	@echo rm -rf $(OBJ_DIR)
	@rm -rf $(OBJ_DIR)
