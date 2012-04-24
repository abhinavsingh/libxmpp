/*
 * xml_element.c
 *
 *  Created on: Apr 22, 2012
 *      Author: abhinavsingh
 */

#include <stdlib.h>

#include "xml_element.h"

xml_element *
xml_element_new(const XML_Char *name, const XML_Char **attrs) {
	xml_element *xmlel;
	xmlel = (xml_element *)malloc(sizeof(xml_element));

	xmlel->name = name;
	xmlel->attrs = attrs;
	xmlel->parent = NULL;
	xmlel->children = NULL;

	return xmlel;
}

void
xml_element_free(xml_element *xmlel) {
	free(xmlel);
}
