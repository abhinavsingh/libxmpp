/*
 * xmpp.c
 *
 *  Created on: Apr 18, 2012
 *      Author: abhinavsingh
 */

#include <stdio.h>
#include <stdlib.h>

#include "xml_stream.h"
#include "xmpp_socket.h"

void
test_xmpp_socket() {
	// create new xmpp socket
	xmpp_socket *sock;
	sock = xmpp_socket_new("127.0.0.1", 5222);

	// connect it to host:port
	xmpp_socket_connect(sock);

	// disconnect socket
	xmpp_socket_disconnect(sock);

	// free sock
	xmpp_socket_free(sock);
}

void
test_xml_stream() {
	xml_stream *xml;
	xml = xml_stream_new();

	xml_stream_parse(xml, "<stream:stream version='1.0'");
	xml_stream_parse(xml, ">body</stream:stream");
	xml_stream_parse_final(xml, ">");

	xml_stream_free(xml);
}

int
main(int argc, char *argv[]) {
	//test_xmpp_socket();
	test_xml_stream();

	return EXIT_SUCCESS;
}
