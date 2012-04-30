/*
 * xmpp.h
 *
 *  Created on: Apr 22, 2012
 *      Author: abhinavsingh
 */

#ifndef XMPP_H_
#define XMPP_H_

#include "xml_stream.h"
#include "xmpp_socket.h"
#include "xmpp_stream.h"
#include "common.h"

struct _xmpp_ctx {
	xmpp_stream *stream;
	xmpp_socket *sock;
	xml_stream *xml;
};

xmpp_ctx *
xmpp_start_client(const char *jid, const char *pass);

#endif /* XMPP_H_ */
