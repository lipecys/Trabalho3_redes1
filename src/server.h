#ifndef SERVER_H
#define SERVER_H

#include <sys/types.h>
#include <sys/socket.h>
#include "biblioteca.h"
#include "fifo.h"
#include "socket.h"

void *servidor (info_pkg *config_node);
#endif /* Fim de SERVER_H */
