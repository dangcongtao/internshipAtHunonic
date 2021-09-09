#
#
#		THIS MAKEFILE IS FAIL TO BUILD ---> I'M TRYING TO CORRECT IT
#		RUN MAKEFILE IN /APP INSTEAD.
NAME_MODULE	= chat_app
CXX			= gcc
CC			= gcc
OBJ_DIR		= build_$(NAME_MODULE)

OPTIMIZE_OPTION	=	-g -O3
WARNNING_OPTION	+=	#-Werror -Wno-missing-field-initializers -W

-include app/Makefile.mk
# -include sources/serial/Makefile.mk
# -include sources/logger/Makefile.mk
# -include sources/database/Makefile.mk
# -include sources/devices/Makefile.mk
# -include sources/networks/mqtt/Makefile.mk

-include third_party/aes/Makefile.mk
-include third_party/cJson/Makefile.mk

# CC compiler option
CFLAGS		+= -I/usr/local/include
CFLAGS		+= -I/usr/include
CFLAGS		+= -I../..
CFLAGS	+=	$(OPTIMIZE_OPTION)	\
		$(WARNNING_OPTION)	\
		-Wall			\
		-Winline		\
		-pipe			\
		-g			\


CXXFLAGS	+= -I/usr/local/include
CXXFLAGS	+= -I/usr/include
CXXFLAGS    += -I../..

# CXX compiler option
CXXFLAGS	+=	$(OPTIMIZE_OPTION)	\
		$(WARNNING_OPTION)	\
		-std=c++11		\
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
		-lpaho-mqtt3as \
		-lpaho-mqttpp3 \

all: create $(OBJ_DIR)/$(NAME_MODULE)

create:
	@echo mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c
	@echo CXX $<
	@$(CXX) -c -o $@ $< $(CXXFLAGS) $(LDFLAGS) $(LDLIBS)

$(OBJ_DIR)/%.o: %.c
	@echo CC $<
	@$(CC) -c -o $@ $< $(CFLAGS) $(LDFLAGS) $(LDLIBS)


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
