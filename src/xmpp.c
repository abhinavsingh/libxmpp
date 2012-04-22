/*
 * xmpp.c
 *
 *  Created on: Apr 18, 2012
 *      Author: abhinavsingh
 */

#include <stdlib.h>

#include "xmpp.h"

xmpp_ctx *
xmpp_start_client(const char *jid, const char *pass) {
	xmpp_ctx *ctx;
	ctx = (xmpp_ctx *)malloc(sizeof(xmpp_ctx));

	// initialize structs
	ctx->stream = xmpp_stream_new(jid, pass);
	ctx->xml = xml_stream_new();
	ctx->sock = xmpp_socket_new("127.0.0.1", 5222);

	// dispatch them in threads
	xml_stream_start(ctx->xml);
	xmpp_stream_start(ctx->stream);
	xmpp_socket_start(ctx->sock);

	return ctx;
}
