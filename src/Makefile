# MAKEFILE - Trabalho 3 de Compiladores
# PROGRAMA:  TokenRing
# DESCRIÇÃO: Chat usando linha de comando em uma rede com topologia 
# em anel.

# Compilador, Opções de Compilação e Arquivos Fonte
CSOURCES=main.c biblioteca.c socket.c
CFLAGS=-Wall
CC=gcc

# Objetos do trabalho
OBJECTS=$(CSOURCES:.c=.o)

# Executavel do projeto
EXEC=tokenring

# Regras de compilação
.PHONY: all
# %.o:
all: $(EXEC) $(OBJECTS)

$(EXEC): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(EXEC)

$(OBJECTS): %.o: %.c
	$(CC) -c $(CFLAGS) $< -o $@

# Regras de limpeza
.PHONY: clean

clean:
	@rm -rf *.bak *.o *~* core* *.out *.gch $(EXEC)
