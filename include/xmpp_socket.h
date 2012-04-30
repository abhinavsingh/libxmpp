/*
 * xmpp_socket.h
 *
 *  Created on: Apr 18, 2012
 *      Author: abhinavsingh
 */

#ifndef XMPP_SOCKET_H_
#define XMPP_SOCKET_H_

#include <unistd.h>
#include <pthread.h>
#include "common.h"

struct _xmpp_socket {
	// event
	struct event_base *base;
	struct event *ev;
	struct bufferevent *buffer;
	pthread_t t;

	// communication link for receiving
	// data to be send over socket from
	// underlying xmpp_stream thread
	int stream[2];

	// connected socket fd
	int fd;

	// socket conf
	const char *ip;
	unsigned short port;
};

xmpp_socket *
xmpp_socket_new(const char *ip, unsigned short port);

void
xmpp_socket_free(xmpp_socket *sock);

void
xmpp_socket_start(xmpp_socket *sock);

void
xmpp_socket_send(xmpp_socket *sock, const char *data);

void
xmpp_socket_stop(xmpp_socket *sock);

#endif /* XMPP_SOCKET_H_ */
