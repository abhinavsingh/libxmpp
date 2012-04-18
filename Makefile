.SUFFIXES:
.SUFFIXES: .c .o

.PHONY: clean

CC = gcc
CFLAGS = -Wall -Iinclude
LDFLAGS = -levent -lexpat
SRCDIR = src
OBJDIR = obj
SRCS = $(addprefix $(SRCDIR)/, xmpp_socket.c xml_stream.c xmpp.c)
OBJS = $(addprefix $(OBJDIR)/, xmpp_socket.o xml_stream.o xmpp.o)
EXE = libxmpp

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXE) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJS) $(EXE)