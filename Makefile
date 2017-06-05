##
## Makefile for  in /home/toune/Documents/Epitech/projets/PSU_2016_myftp
## 
## Made by Thomas HENON
## Login   <thomas.henon@epitech.eu>
## 
## Started on  Thu May 18 10:29:51 2017 Thomas HENON
## Last update Thu May 18 10:29:53 2017 Thomas HENON
##

CC = gcc

RM = rm -f

SERVER_NAME = server
CLIENT_NAME = client

COMMON_SRCS = src/common/network/socket.c \
              src/common/network/socket2.c \
              src/common/network/socket_server.c \
              src/common/util.c \
              src/common/error.c \
              src/common/generic_list.c \
              src/common/generic_list2.c \
              src/common/cbuffer.c \
              src/common/cbuffer2.c \
              src/common/my_select.c \
              src/common/packet.c \
              src/common/packet2.c \
              src/common/packet_parser.c \
              src/common/channel.c \
              src/common/channel2.c

SERVER_SRCS =   $(COMMON_SRCS) \
                src/server/client.c \
                src/server/client2.c \
                src/server/commands.c \
                src/server/commands2.c \
                src/server/main.c \
                src/server/server.c \
                src/server/server_commands.c \
                src/server/channel_commands.c \
                src/server/select.c \
                src/server/packet.c

CLIENT_SRCS =   $(COMMON_SRCS) \
                src/client/main.c \
                src/client/cli_commands.c \
                src/client/cli_commands2.c \
                src/client/commands.c \
                src/client/commands2.c \
                src/client/commands3.c \
                src/client/packet.c \
                src/client/channel.c \
                src/client/cli.c \
                src/client/cli2.c \
                src/client/client.c \
                src/client/select.c

SERVER_OBJS = $(SERVER_SRCS:.c=.o)
CLIENT_OBJS = $(CLIENT_SRCS:.c=.o)

LDFLAGS+= -g

CFLAGS+= -I./includes -g

all: server client

server: $(SERVER_OBJS)
	$(CC) -o $(SERVER_NAME) $(SERVER_OBJS) $(LDFLAGS)

client: $(CLIENT_OBJS)
	$(CC) -o $(CLIENT_NAME) $(CLIENT_OBJS) $(LDFLAGS)

clean:
	$(RM) $(SERVER_OBJS)
	$(RM) $(CLIENT_OBJS)

fclean: clean
	$(RM) $(SERVER_NAME)
	$(RM) $(CLIENT_NAME)

re: fclean all

.PHONY: all clean fclean re
