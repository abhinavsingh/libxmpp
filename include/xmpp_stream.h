/*
 * xmpp_stream.h
 *
 *  Created on: Apr 18, 2012
 *      Author: abhinavsingh
 */

#ifndef XMPP_STREAM_H_
#define XMPP_STREAM_H_

typedef struct _xmpp_socket xmpp_socket;
typedef struct _xmpp_xml_stream xmpp_xml_stream;

typedef struct _xmpp_stream xmpp_stream;
struct _xmpp_stream {
	const char *jid;
	const char *password;

	xmpp_socket *socket;
	xmpp_xml_stream *xml;
};

#endif /* XMPP_STREAM_H_ */
