CXXFLAGS	+= -I./app

VPATH += app

OBJ += $(OBJ_DIR)/udp_broadcast.o $(OBJ_DIR)/tcp_server.o $(OBJ_DIR)/main.o
