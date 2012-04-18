/*
 * xml_stream.h
 *
 *  Created on: Apr 18, 2012
 *      Author: abhinavsingh
 */

#ifndef XML_STREAM_H_
#define XML_STREAM_H_

#include <expat.h>

typedef struct _xml_stream xml_stream;
struct _xml_stream {
	int depth;
	XML_Parser parser;
};

xml_stream *
xml_stream_new();

void
xml_stream_free(xml_stream *xml);

void
xml_stream_parse(xml_stream *xml, const char *s);

void
xml_stream_parse_final(xml_stream *xml, const char *s);

#endif /* XML_STREAM_H_ */
