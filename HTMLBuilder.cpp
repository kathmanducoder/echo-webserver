#include <iostream>

#include "HTMLBuilder.h"

int HTMLBuilder::build_html(char html[], int html_len, char content[]) {
    int             string_index = 0;
    char            *token = NULL;

    string_index = snprintf(html, html_len, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
                            "<html>",
                            "<head>",
                            "<title>http_webserv</title>",
                            /* For bootstrap*/
                            "<link href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css\" rel=\"stylesheet\" integrity=\"sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC\" crossorigin=\"anonymous\">",
                            "</head>",
                            "<body>",
                            "<ul style=\"list-style-type: none;\">");

    string_index += snprintf(html + string_index, html_len, "%s\n", "<ul style=\"list-style-type: none;\">");

    token = strtok(content, "\n");
    while (token != NULL) {
        string_index += snprintf(html + string_index, html_len, "<li>%s</li>", token);
        token = strtok(NULL, "\n");
    }
    string_index += snprintf(html + string_index, html_len, "%s\n%s\n%s\n", "</ul>", "</body>", "</html>");

    html[string_index] = '\0';

    return 0;
}