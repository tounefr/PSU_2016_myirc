/*
** packet_parser.c for  in /home/toune/Documents/Epitech/projets/PSU_2016_myirc
** 
** Made by Thomas HENON
** Login   <thomas.henon@epitech.eu>
** 
** Started on  Sun May 28 00:03:25 2017 Thomas HENON
** Last update Sun May 28 00:03:26 2017 Thomas HENON
*/

#include "server.h"

static char *
get_ptr_content(char *buffer)
{
    int i;

    i = -1;
    while (buffer[++i]) {
        if (buffer[i] == ' ' && buffer[i + 1] == ':')
            return &buffer[i + 2];
    }
    return NULL;
}

char
*parse_packet_prefix_dst(t_packet *packet)
{
    char *dst;
    char *nickname;
    char *tmp;

    dst = my_strdup(packet->prefix);
    tmp = dst;
    if (!(nickname = strtok(dst, "!")))
        return NULL;
    nickname = my_strdup(nickname);
    free(tmp);
    return nickname;
}

static void
debug_packet(t_packet *packet)
{
    printf("==[PACKET]==\nnbr_params %d\n", packet->nbr_params);
    printf("prefix : :%s\n", packet->prefix);
    printf("cmd : %s\n", packet->cmd);
    for (int i = 0; i < IRC_PACKET_NBR_PARAMS; i++) {
        printf("params[%d] = %s\n", i, packet->params[i]);
    }
    printf("content : %s\n", packet->content);
    printf("====\n");
}

char
parse_prefix(t_packet *packet, char *prefix)
{

}

char
simple_space_parser(t_packet *packet)
{
    char *token;
    int i;
    char *buffer;
    char *tmp;

    buffer_rm_crlf(packet->raw);
    buffer = strdup_irc_packet(packet->raw);
    tmp = buffer;
    i = 0;
    while ((token = strtok(buffer, " "))) {
        buffer = NULL;
        if (i == 0 && token[0] == ':' && !packet->prefix)
            packet->prefix = my_strdup(&token[1]);
        else if (token[0] == ':') {
            packet->content = my_strdup(get_ptr_content(packet->raw));
           // debug_packet(packet);
            return 1;
        }
        else if (!packet->cmd)
            packet->cmd = my_strdup(token);
        else
            packet->params[packet->nbr_params++] = my_strdup(token);
        i++;
    }
//    debug_packet(packet);
//    free(tmp);
    return 1;
}

char
*strdup_irc_packet(char *buffer)
{
    char *new_buffer;

    new_buffer = my_malloc(IRC_PACKET_SIZE);
    memcpy(new_buffer, buffer, IRC_PACKET_SIZE);
    return new_buffer;
}
