#include <iostream>

#include "HTMLBuilder.h"

int HTMLBuilder::build_html(char html[], int html_len, char content[], char *client_ip) {
    int             string_index = 0;
    char            *token = NULL;

    string_index = snprintf(html, html_len, "%s\n%s\n%s\n%s\n%s\n",
                            "<html>",
                            "<head>",
                            "<title>echowebserver</title>",
                            /* For bootstrap*/
                            "<link href=\"https://cdn.jsdelivr.net/npm/bootstrap@5.0.2/dist/css/bootstrap.min.css\" rel=\"stylesheet\" integrity=\"sha384-EVSTQN3/azprG1Anm3QDgpJLIm9Nao0Yz1ztcQTwFspd3yD65VohhpuuCOmLASjC\" crossorigin=\"anonymous\">",
                            "</head>");

    string_index += snprintf(html + string_index, html_len, "%s\n%s\n%s\n%s\n%s\n%s%s%s\n%s\n%s\n%s\n",
                             "<body style=\"background-image: linear-gradient(to bottom right, #7F8C8D, #000000);\">",
                             "<div class=\"container\">",
                             "<div class=\"row row-top-buffer justify-content-center\">",
                             "<div class=\"col-lg-8\">",
                             "<div class=\"card shadow p-3 mt-5 mb-3 bg-secondary rounded text-muted\">",
                             "<div style=\"margin:10px; font-weight:bold; text-align:center; color:#E57254; font-size: 24px;\"> The webserver sees your IP : ",
                             client_ip,
                             "</div>",
                             "</div>",
                             "</div>",
                             "</div>");

    string_index += snprintf(html + string_index, html_len, "%s\n%s\n%s\n%s\n%s\n",
                             "<div class=\"row row-top-buffer justify-content-center\">",
                             "<div class=\"col-lg-8\">",
                             "<div class=\"card bg-dark shadow p-3 mt-3 mb-3 rounded text-muted\">",
                             "<ul style=\"list-style-type: none;\">",
                             "<li style=\"margin:10px; font-size: 22px; text-align:center; color:#46BCDE;\"> Here is what else the server sees in the request header</li>");


    token = strtok(content, "\n");
    while (token != NULL) {
        string_index += snprintf(html + string_index, html_len, "<li style=\"margin:4px;\">%s</li>", token);
        token = strtok(NULL, "\n");
    }

    /* Closing tags*/
    string_index += snprintf(html + string_index, html_len, "%s\n%s\n%s\n%s\n%s\n%s\n%s\n",
                            "</ul>",
                            "</div>",
                            "</div>",
                            "</div>",
                            "</div>",
                            "</body>",
                            "</html>");

    html[string_index] = '\0';

    return 0;
}