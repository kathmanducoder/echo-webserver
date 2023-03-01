#include <iostream>

#include "HTMLBuilder.h"

int HTMLBuilder::build_html(char html[], int html_len, char content[]) {
    int             html_num_bytes;

    html_num_bytes = snprintf(html, html_len, "%s\n%s\n%s\n", "<html>", content, "</html>");
    html[html_num_bytes] = '\0';

    return 0;
}