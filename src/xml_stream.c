/*
 * xml_stream.c
 *
 *  Created on: Apr 18, 2012
 *      Author: abhinavsingh
 */

#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <event2/event.h>

#include "xml_stream.h"

static void XMLCALL
xml_stream_start_element(void *arg, const XML_Char *name, const XML_Char **attrs) {
	xml_stream *xml;
	xml = (xml_stream *)arg;
	//printf("start of %s\n", name);

	xml->depth++;
}

static void XMLCALL
xml_stream_end_element(void *arg, const XML_Char *name) {
	xml_stream *xml;
	xml = (xml_stream *)arg;
	//printf("end of %s\n", name);

	xml->depth--;
}

static void XMLCALL
xml_stream_data(void *arg, const XML_Char *data, int len) {
	//xml_stream *xml;
	//xml = (xml_stream *)arg;
}

static void
xml_stream_parse_data(int pipefd, short event, void *ptr) {
	xml_stream *xml;
	xml = (xml_stream *)ptr;

	char buf[1024];
	int ret;

	ret = read(pipefd, &buf, 1024);
	ret = XML_Parse(xml->parser, buf, ret, 0);
	assert(ret != 0);
}

static void *
xml_stream_main(void *arg) {
	xml_stream *xml;
	xml = (xml_stream *)arg;

	// monitor pipe
	xml->base = event_base_new();
	xml->ev = event_new(xml->base, xml->sock[0], EV_READ | EV_PERSIST, xml_stream_parse_data, xml);
	event_add(xml->ev, NULL);

	// setup expat callbacks
	XML_SetUserData(xml->parser, xml);
	XML_SetElementHandler(xml->parser, xml_stream_start_element, xml_stream_end_element);
	XML_SetCharacterDataHandler(xml->parser, xml_stream_data);

	// loop
	//printf("dispatching xml stream loop\n");
	event_base_dispatch(xml->base);

	return NULL;
}

//
// Public API
//

xml_stream *
xml_stream_new() {
	int ret;

	xml_stream *xml;
	xml = (xml_stream *)malloc(sizeof(xml_stream));

	xml->depth = 0;
	xml->parser = XML_ParserCreate(NULL);
	ret = pipe(xml->sock);
	(void)ret;

	return xml;
}

void
xml_stream_free(xml_stream *xml) {
	int i;
	void *res;

	i = pthread_cancel(xml->t);
	assert(i == 0);

	i = pthread_join(xml->t, &res);
	assert(i == 0);
	assert(res == PTHREAD_CANCELED);

	XML_ParserFree(xml->parser);
	event_del(xml->ev);
	event_free(xml->ev);
	event_base_free(xml->base);
	free(xml);
}

void
xml_stream_parse(xml_stream *xml, const char *data) {
	int ret = write(xml->sock[1], data, strlen(data));
	//printf("sent %d bytes\n", ret);
	(void)ret;
}

void
xml_stream_parse_final(xml_stream *xml, const char *data) {
	int ret = write(xml->sock[1], data, strlen(data));
	//printf("sent %d bytes\n", ret);
	(void)ret;
}

void
xml_stream_start(xml_stream *xml) {
	//printf("threading xml stream\n");
	pthread_create(&xml->t, NULL, xml_stream_main, xml);
}
