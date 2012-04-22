/*
 * xmpp_stream.c
 *
 *  Created on: Apr 18, 2012
 *      Author: abhinavsingh
 */

#include <stdlib.h>

#include <event2/event.h>
#include <event2/event_compat.h>

#include "xml_stream.h"
#include "xmpp_socket.h"
#include "xmpp_stream.h"

static void
xmpp_stream_process(int pipefd, short event, void *ptr) {
	// drain incoming xml element from messaging pipe

	// process and update fsm state
	// if necessary send more data over socket
	// if necessary send callback to user landspace
}

static void *
xmpp_stream_main(void *arg) {
	xmpp_stream *stream;
	stream = (xmpp_stream *)arg;

	// monitor pipe
	stream->base = event_base_new();
	event_set(stream->ev, stream->xml[0], EV_READ | EV_PERSIST, xmpp_stream_process, stream);
	event_base_set(stream->base, stream->ev);
	event_add(stream->ev, NULL);

	// loop
	event_base_dispatch(stream->base);

	return NULL;
}

//
// Public API
//

xmpp_stream *
xmpp_stream_new(const char *jid, const char *pass) {
	int ret;

	xmpp_stream *stream;
	stream = (xmpp_stream *)malloc(sizeof(xmpp_stream));

	stream->jid = jid;
	stream->pass = pass;

	ret = pipe(stream->xml);
	(void)ret;

	return stream;
}

void
xmpp_stream_free(xmpp_stream *stream) {
	free(stream);
}

void
xmpp_stream_start(xmpp_stream *stream) {
	pthread_create(&stream->t, NULL, xmpp_stream_main, stream);
}
