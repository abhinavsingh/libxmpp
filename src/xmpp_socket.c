/*
 * xmpp_socket.c
 *
 *  Created on: Apr 18, 2012
 *      Author: abhinavsingh
 */

#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <assert.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <event2/event.h>
#include <event2/bufferevent.h>

#include "xmpp_socket.h"

xmpp_socket *
xmpp_socket_new(const char *ip, unsigned short port) {
	xmpp_socket *sock;
	sock = (xmpp_socket *)malloc(sizeof(xmpp_socket));

	sock->ip = ip;
	sock->port = port;

	return sock;
}

void
xmpp_socket_free(xmpp_socket *sock) {
	free(sock);
}

void
xmpp_socket_connect(xmpp_socket *sock) {
	int ret;
	struct sockaddr_in addr;

	addr.sin_family = AF_INET;
	addr.sin_port = htons(sock->port);
	memset(&(addr.sin_addr), 0, sizeof(addr.sin_addr));
	addr.sin_addr.s_addr = inet_addr(sock->ip);

	sock->fd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	assert(sock->fd != -1);

	ret = connect(sock->fd, (struct sockaddr *)&addr, sizeof(addr));
	assert(ret == 0);

	ret = evutil_make_socket_nonblocking(sock->fd);
	assert(ret == 0);

	sock->base = event_base_new();
	sock->buffer = bufferevent_socket_new(sock->base, sock->fd, BEV_OPT_CLOSE_ON_FREE);
	bufferevent_enable(sock->buffer, EV_READ|EV_WRITE);
}

void
xmpp_socket_disconnect(xmpp_socket *sock) {
	bufferevent_free(sock->buffer);
	event_base_free(sock->base);
	close(sock->fd);
}

void
xmpp_socket_send(xmpp_socket *sock, char *data) {

}

void
xmpp_socket_recv(xmpp_socket *sock) {

}
