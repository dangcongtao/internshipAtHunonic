NAME_MODULE	= read_example
OBJ_DIR		= build_$(NAME_MODULE)

LDFLAGS	+= -Wl,-Map=$(OBJ_DIR)/$(NAME_MODULE).map

-include ./Makefile.mk

all: create $(OBJ_DIR)/$(NAME_MODULE)

create:
	@echo mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: %.c
	@echo CXX $<
	@$(CXX) -c -o $@ $< $(CXXFLAGS) $(CFLAGS) $(LDFLAGS) $(LDLIBS)

$(OBJ_DIR)/%.o: %.c
	@echo CC $<
	@$(CC) -c -o $@ $< $(CFLAGS) $(LDFLAGS) $(LDLIBS)

# $(OBJ_DIR)/$(NAME_MODULE): $(OBJ)
# 	@echo ---------- START LINK PROJECT ----------
# 	@echo $(CC) -o $@ $^ $(LDFLAGS)
# 	@$(CC) -o $@ $^ $(LDFLAGS) $(LDLIBS)

# $(OBJ_DIR)/$(NAME_MODULE): $(OBJ)
# 	@echo ---------- START LINK CPP PROJECT ----------
# 	@echo $(CXX) -o $@ $^ $(CXXFLAGS)
# 	@$(CXX) -o $@ $^ $(CXXFLAGS) $(LDFLAGS) $(LDLIBS)

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