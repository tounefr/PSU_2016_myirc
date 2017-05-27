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
SERVER_SRCS =   src/common/my_select.c \
                src/common/network/socket.c \
                src/common/network/socket2.c \
                src/common/network/socket_server.c \
                src/common/util.c \
                src/common/error.c \
                src/server/cbuffer.c \
                src/server/client.c \
                src/server/commands.c \
                src/server/main.c \
                src/server/server.c \
                src/server/packet_parser.c \
                src/server/packet.c \
                src/server/server_commands.c \
                src/server/channel_commands.c \
                src/server/channel.c

SERVER_OBJS = $(SERVER_SRCS:.c=.o)

CLIENT_NAME = client
CLIENT_SRCS = src/client/main.c
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
