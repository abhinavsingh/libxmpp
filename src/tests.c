/*
 * tests.c
 *
 *  Created on: Apr 22, 2012
 *      Author: abhinavsingh
 */

#include <stdio.h>
#include <stdlib.h>

#include "xmpp.h"
#include "tests.h"

void
test_xmpp_socket() {
	// create new xmpp socket
	xmpp_socket *sock;
	sock = xmpp_socket_new("127.0.0.1", 5222);

	// start socket (implies connect)
	xmpp_socket_start(sock);

	// send some data
	sleep(1);
	char *data = "<stream:stream>";
	xmpp_socket_send(sock, data);

	sleep(2);
	// implies disconnect
	xmpp_socket_stop(sock);

	// free sock
	xmpp_socket_free(sock);
}

void
test_xml_stream() {
	xml_stream *xml;
	xml = xml_stream_new();

	xml_stream_start(xml);
	sleep(3);

	xml_stream_parse(xml, "<stream:stream version='1.0'");
	xml_stream_parse(xml, ">body</stream:stream");
	xml_stream_parse_final(xml, ">");

	sleep(2);
	//xml_stream_free(xml);
}

void
test_xmpp_stream() {
	xmpp_stream *client;
	client = xmpp_stream_new("root@jaxl.com", "lifeislife");
	xmpp_stream_connect(client);
	xmpp_stream_start(client);
	xmpp_stream_disconnect(client);
	xmpp_stream_free(client);
}

int
main(int argc, char *argv[]) {
	//test_xmpp_socket();
	test_xml_stream();

	//xmpp_ctx *ctx;
	//ctx = xmpp_start_client("root@typed.in", "lifeislife");

	return EXIT_SUCCESS;
}
