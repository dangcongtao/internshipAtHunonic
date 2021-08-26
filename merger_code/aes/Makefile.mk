CXXFLAGS	+= -I./aes

VPATH += aes

OBJ += $(OBJ_DIR)/aes.o $(OBJ_DIR)/aes_cbc128.o $(OBJ_DIR)/base64.o
