#ifndef CLIENT_H
#define CLIENT_H

#include <sys/types.h>
#include <sys/socket.h>
#include "biblioteca.h"
#include "fifo.h"
#include "socket.h"

void *cliente (info_pkg *config_node);
#endif /* Fim de CLIENT_H */
