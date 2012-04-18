/*
 * xml_stream.c
 *
 *  Created on: Apr 18, 2012
 *      Author: abhinavsingh
 */

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "xml_stream.h"

static void XMLCALL
xml_stream_start_element(void *arg, const XML_Char *name, const XML_Char **attrs) {
	xml_stream *xml;
	xml = (xml_stream *)arg;
	xml->depth++;
}

static void XMLCALL
xml_stream_end_element(void *arg, const XML_Char *name) {
	xml_stream *xml;
	xml = (xml_stream *)arg;
	xml->depth--;
}

static void XMLCALL
xml_stream_data(void *arg, const XML_Char *data, int len) {
	//xml_stream *xml;
	//xml = (xml_stream *)arg;
}

xml_stream *
xml_stream_new() {
	xml_stream *xml;
	xml = (xml_stream *)malloc(sizeof(xml_stream));

	xml->depth = 0;
	xml->parser = XML_ParserCreate(NULL);

	XML_SetUserData(xml->parser, xml);
	XML_SetElementHandler(xml->parser, xml_stream_start_element, xml_stream_end_element);
	XML_SetCharacterDataHandler(xml->parser, xml_stream_data);

	return xml;
}

void
xml_stream_free(xml_stream *xml) {
	XML_ParserFree(xml->parser);
	free(xml);
}

void
xml_stream_parse(xml_stream *xml, const char *s) {
	int ret;
	ret = XML_Parse(xml->parser, s, strlen(s), 0);
	assert(ret != 0);
}

void
xml_stream_parse_final(xml_stream *xml, const char *s) {
	int ret;
	ret = XML_Parse(xml->parser, s, strlen(s), 0);
	assert(ret != 0);
}
