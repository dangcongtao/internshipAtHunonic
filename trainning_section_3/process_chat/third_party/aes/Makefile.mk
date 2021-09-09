CXXFLAGS	+= -I./sources/third_party/aes

VPATH += sources/third_party/aes

OBJ += $(OBJ_DIR)/aes.o $(OBJ_DIR)/aes_cbc128.o $(OBJ_DIR)/base64.o
