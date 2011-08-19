/* Infineon X-Gold RIL
**
** Copyright 2006, The Android Open Source Project
**
** Licensed under the Apache License, Version 2.0 (the "License");
** you may not use this file except in compliance with the License.
** You may obtain a copy of the License at
**
**     http://www.apache.org/licenses/LICENSE-2.0
**
** Unless required by applicable law or agreed to in writing, software
** distributed under the License is distributed on an "AS IS" BASIS,
** WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
** See the License for the specific language governing permissions and
** limitations under the License.
**
** Based on reference-ril by - Copyright 2006, The Android Open Source Project
** Modified September 2009 by Texas Instruments
*/
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <cutils/properties.h>

/** returns 1 if line starts with prefix, 0 if it does not */
int strStartsWith(const char *line, const char *prefix)
{
    for ( ; *line != '\0' && *prefix != '\0' ; line++, prefix++) {
        if (*line != *prefix) {
            return 0;
        }
    }

    return *prefix == '\0';
}

/**
* Very simple function that extract and returns whats between ElementBeginTag
* and ElementEndTag.
*
* Optional ppszRemainingDocument that can return a pointer to the remaining
* of the document to be "scanned". This can be used if subsequent
* scanning/searching is desired.
*
* This function is used to extract the parameters from the XML result
* returned by U3xx during a PDP Context setup, and used to parse the
* tuples of operators returned from AT+COPS.
*
* const char* document - Document to be scanned
* const char* elementBeginTag - Begin tag to scan for, return whats
* between begin/end tags
* const char* elementEndTag - End tag to scan for, return whats
* between begin/end tags
* char** remainingDocumen t - Can return the a pointer to the remaining
* of pszDocument, this parameter is optional
*
* return char* containing whats between begin/end tags, allocated on the
* heap, need to free this.
* return NULL if nothing is found.
*/
char *getFirstElementValue(const char *document,
                           const char *elementBeginTag,
                           const char *elementEndTag,
                           char **remainingDocument)
{
    char *value = NULL;
    char *start = NULL;
    char *end = NULL;

    if (document != NULL && elementBeginTag != NULL
        && elementEndTag != NULL) {
        start = strstr(document, elementBeginTag);
        if (start != NULL) {
            end = strstr(start, elementEndTag);
            if (end != NULL) {
                int n = strlen(elementBeginTag);
                int m = end - (start + n);
                value = (char *) malloc((m + 1) * sizeof(char));
                strncpy(value, (start + n), m);
                value[m] = (char) 0;

                /* Optional, return a pointer to the remaining document,
to be used when document contains many tags with same name. */
                if (remainingDocument != NULL)
                    *remainingDocument = end + strlen(elementEndTag);
            }
        }
    }
    return value;
}