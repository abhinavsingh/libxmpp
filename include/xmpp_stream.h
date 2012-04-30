/*
 * xmpp_stream.h
 *
 *  Created on: Apr 18, 2012
 *      Author: abhinavsingh
 */

#ifndef XMPP_STREAM_H_
#define XMPP_STREAM_H_

#include <unistd.h>
#include <pthread.h>
#include "common.h"

struct _xmpp_stream {
	// event
	struct event_base *base;
	struct event *ev;
	pthread_t t;

	// communication link for receiving parsed
	// xml elements from xml stream thread
	int xml[2];

	const char *jid;
	const char *pass;
};

xmpp_stream *
xmpp_stream_new(const char *jid, const char *pass);

void
xmpp_stream_free(xmpp_stream *stream);

void
xmpp_stream_connect(xmpp_stream *stream);

void
xmpp_stream_disconnect(xmpp_stream *stream);

void
xmpp_stream_start(xmpp_stream *stream);

void
xmpp_stream_stop(xmpp_stream *stream);

#endif /* XMPP_STREAM_H_ */
