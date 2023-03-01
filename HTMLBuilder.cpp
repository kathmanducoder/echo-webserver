#include <iostream>

#include "HTMLBuilder.h"

int HTMLBuilder::build_html(char html[], int html_len, char content[]) {
    int             string_index = 0;

    string_index = snprintf(html, html_len, "%s\n%s\n%s\n", "<html>", "<body>", "<ul>");
    string_index += snprintf(html + string_index, html_len, "%s\n", content);
    string_index += snprintf(html + string_index, html_len, "%s\n%s\n%s\n", "</ul>", "</body>", "</html>");

    html[string_index] = '\0';

    return 0;
}