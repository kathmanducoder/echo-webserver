#include <iostream>

#include "HTMLBuilder.h"

int HTMLBuilder::build_html(char html[], int html_len, char content[]) {
    int             string_index = 0;
    char            *token = NULL;

    string_index = snprintf(html, html_len, "%s\n%s\n%s\n", "<html>", "<body>", "<ul style=\"list-style-type: none;\">");

    token = strtok(content, "\n");
    while (token != NULL) {
        string_index += snprintf(html + string_index, html_len, "<li>%s</li>", token);
        token = strtok(NULL, "\n");
    }
    string_index += snprintf(html + string_index, html_len, "%s\n%s\n%s\n", "</ul>", "</body>", "</html>");

    html[string_index] = '\0';

    return 0;
}