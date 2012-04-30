/*
 * xml_stream.h
 *
 *  Created on: Apr 18, 2012
 *      Author: abhinavsingh
 */

#ifndef XML_STREAM_H_
#define XML_STREAM_H_

#include <expat.h>
#include <unistd.h>
#include <pthread.h>
#include "common.h"

struct _xml_stream {
	// event
	struct event_base *base;
	struct event *ev;
	pthread_t t;

	// communication link for receiving raw
	// socket data from xmpp_socket thread
	int sock[2];

	int depth;
	XML_Parser parser;
};

xml_stream *
xml_stream_new();

void
xml_stream_start(xml_stream *xml);

void
xml_stream_free(xml_stream *xml);

void
xml_stream_parse(xml_stream *xml, const char *data);

void
xml_stream_parse_final(xml_stream *xml, const char *data);

#endif /* XML_STREAM_H_ */
