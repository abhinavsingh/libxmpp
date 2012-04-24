/*
 * xml_element.h
 *
 *  Created on: Apr 22, 2012
 *      Author: abhinavsingh
 */

#ifndef XML_ELEMENT_H_
#define XML_ELEMENT_H_

#include <expat.h>

typedef struct _xml_element xml_element;
struct _xml_element {
	const XML_Char *name;
	const XML_Char **attrs;
	const XML_Char *data;

	struct _xml_element *parent;
	struct _xml_element *children;
};

xml_element *
xml_element_new(const XML_Char *name, const XML_Char **attrs);

void
xml_element_free(xml_element *xmlel);

#endif /* XML_ELEMENT_H_ */
