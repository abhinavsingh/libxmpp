/*
 * xmpp_socket.c
 *
 *  Created on: Apr 18, 2012
 *      Author: abhinavsingh
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <event2/event.h>
#include <event2/buffer.h>
#include <event2/bufferevent.h>

#include "xmpp_socket.h"

static void
xmpp_socket_readcb(struct bufferevent *buffer, void *arg) {
	int n;
	char buf[1024];

	struct evbuffer *in = bufferevent_get_input(buffer);
	//printf("got read cb\n");
	while((n = evbuffer_remove(in, buf, sizeof(buf))) > 0) {
		//fwrite(buf, 1, n, stdout);
	}
	//printf("\n");
}

static void
xmpp_socket_writecb(struct bufferevent *buffer, void *arg) {
	//printf("got write cb\n");
}

static void
xmpp_socket_eventcb(struct bufferevent *buffer, short events, void *arg) {
	//printf("got event cb\n");

	if(events & BEV_EVENT_ERROR) {
		//printf("got error\n");
	}
	else if(events & BEV_EVENT_EOF) {
		//printf("got eof\n");
	}
}

void
xmpp_socket_setup(xmpp_socket *sock) {
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

	sock->buffer = bufferevent_socket_new(sock->base, sock->fd, BEV_OPT_CLOSE_ON_FREE);
	bufferevent_setcb(sock->buffer, xmpp_socket_readcb, xmpp_socket_writecb, xmpp_socket_eventcb, sock);
	bufferevent_enable(sock->buffer, EV_READ|EV_WRITE);
}

void
xmpp_socket_disconnect(xmpp_socket *sock) {
	bufferevent_free(sock->buffer);
	event_base_free(sock->base);
	close(sock->fd);
}

static void
xmpp_socket_send_data(int pipefd, short event, void *ptr) {
	xmpp_socket *sock;
	sock = (xmpp_socket *)ptr;

	char buf[1024];
	int ret;

	ret = read(pipefd, &buf, 1024);
	//fwrite(&buf, 1, ret, stdout);
	bufferevent_write(sock->buffer, &buf, ret);
	//printf("got %d bytes from pipe\n", ret);
}

static void *
xmpp_socket_main(void *arg) {
	xmpp_socket *sock;
	sock = (xmpp_socket *)arg;

	// monitor pipe
	sock->base = event_base_new();
	sock->ev = event_new(sock->base, sock->stream[0], EV_READ | EV_PERSIST, xmpp_socket_send_data, sock);
	event_add(sock->ev, NULL);

	// setup socket
	xmpp_socket_setup(sock);

	// loop
	//printf("dispatching socket loop\n");
	event_base_dispatch(sock->base);

	return NULL;
}

//
// API Methods
//

xmpp_socket *
xmpp_socket_new(const char *ip, unsigned short port) {
	int ret;

	xmpp_socket *sock;
	sock = (xmpp_socket *)malloc(sizeof(xmpp_socket));

	sock->ip = ip;
	sock->port = port;

	ret = pipe(sock->stream);
	(void)ret;

	return sock;
}

void
xmpp_socket_free(xmpp_socket *sock) {
	int i;
	void *res;

	i = pthread_cancel(sock->t);
	assert(i == 0);

	i = pthread_join(sock->t, &res);
	assert(i == 0);
	assert(res == PTHREAD_CANCELED);

	event_del(sock->ev);
	event_free(sock->ev);
	bufferevent_free(sock->buffer);
	event_base_free(sock->base);
	free(sock);
}

void
xmpp_socket_send(xmpp_socket *sock, const char *data) {
	int ret = write(sock->stream[1], data, strlen(data));
	//printf("sent %d bytes\n", ret);
	(void)ret;
}

void
xmpp_socket_start(xmpp_socket *sock) {
	//printf("threading xmpp socket\n");
	pthread_create(&sock->t, NULL, xmpp_socket_main, sock);
}
