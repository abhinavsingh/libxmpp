.SUFFIXES:
.SUFFIXES: .c .o

.PHONY: clean

CC = gcc
CFLAGS = -Wall -Iinclude
LDFLAGS = -levent -lexpat -pthread
SRCDIR = src
OBJDIR = obj
SRCS = $(addprefix $(SRCDIR)/, xmpp_stream.c xmpp_socket.c xml_stream.c tests.c xmpp.c)
OBJS = $(addprefix $(OBJDIR)/, xmpp_stream.o xmpp_socket.o xml_stream.o tests.o xmpp.o)
EXE = libxmpp

$(EXE): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(EXE) $(LDFLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm $(OBJS) $(EXE)