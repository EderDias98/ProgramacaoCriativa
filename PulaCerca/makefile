# Nome do seu programa
TARGET = meu_programa

# Compilador
CC = gcc

# Flags de compilação
CFLAGS = -Wall -Wextra -Werror -std=c99

# Diretórios de código-fonte, cabeçalhos e de compilação
SRCDIR = .
INCDIR = .
BUILDDIR = .

# Extensões dos arquivos
SRCEXT = c
HDREXT = h

# Lista de arquivos fonte
SRCS = $(wildcard *.$(SRCEXT))

# Lista de arquivos objetos correspondentes
OBJS = $(patsubst %.$(SRCEXT),%.o,$(SRCS))

# Comando de compilação
$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

# Comando de compilação para cada arquivo objeto
%.o: %.$(SRCEXT)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

# Comando para limpar os arquivos objeto e o executável
clean:
	rm -f *.$(SRCEXT) *.o $(TARGET)

# Faz com que os alvos clean e $(TARGET) não sejam confundidos com arquivos
.PHONY: clean $(TARGET)