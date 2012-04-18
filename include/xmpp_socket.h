/*
 * xmpp_socket.h
 *
 *  Created on: Apr 18, 2012
 *      Author: abhinavsingh
 */

#ifndef XMPP_SOCKET_H_
#define XMPP_SOCKET_H_

typedef struct _xmpp_socket xmpp_socket;
struct _xmpp_socket {
	const char *ip;
	unsigned short port;

	int fd;
	struct event_base *base;
	struct bufferevent *buffer;
};

xmpp_socket *
xmpp_socket_new(const char *ip, unsigned short port);

void
xmpp_socket_free(xmpp_socket *sock);

void
xmpp_socket_connect(xmpp_socket *sock);

void
xmpp_socket_disconnect(xmpp_socket *sock);

void
xmpp_socket_send(xmpp_socket *sock, char *data);

void
xmpp_socket_recv(xmpp_socket *sock);

#endif /* XMPP_SOCKET_H_ */
