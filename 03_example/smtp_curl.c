#include <stdio.h>
#include <string.h>
#include <curl/curl.h>

#define FROM    "<your_email@gmail.com>"
#define TO      "<recipient@example.com>"
#define CC      "<cc@example.com>"

// Email content
static const char *payload_text[] = {
  "To: " TO "\r\n",
  "Cc: " CC "\r\n",
  "From: " FROM "\r\n",
  "Subject: SMTP email via libcurl\r\n",
  "\r\n", // Empty line to divide headers from body
  "Hello Craig,\r\n",
  "This is a test email sent from a C program using libcurl.\r\n",
  "Best,\r\n",
  "Your App\r\n",
  NULL
};

// Callback to provide email data line-by-line
static size_t payload_source(void *ptr, size_t size, size_t nmemb, void *userp) {
    const char **payload = (const char **)userp;
    if (*payload) {
        size_t len = strlen(*payload);
        memcpy(ptr, *payload, len);
        (*payload)++;
        return len;
    }
    return 0;
}

int main(void) {
    CURL *curl;
    CURLcode res = CURLE_OK;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "smtp://smtp.gmail.com:587");
        curl_easy_setopt(curl, CURLOPT_USE_SSL, (long)CURLUSESSL_ALL);
        curl_easy_setopt(curl, CURLOPT_USERNAME, "your_email@gmail.com");
        curl_easy_setopt(curl, CURLOPT_PASSWORD, "your_app_password"); // Use App Password for Gmail
        curl_easy_setopt(curl, CURLOPT_MAIL_FROM, FROM);

        struct curl_slist *recipients = NULL;
        recipients = curl_slist_append(recipients, TO);
        recipients = curl_slist_append(recipients, CC);
        curl_easy_setopt(curl, CURLOPT_MAIL_RCPT, recipients);

        curl_easy_setopt(curl, CURLOPT_READFUNCTION, payload_source);
        curl_easy_setopt(curl, CURLOPT_READDATA, &payload_text);
        curl_easy_setopt(curl, CURLOPT_UPLOAD, 1L);

        // Optional: for verbose output
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        // Send the message
        res = curl_easy_perform(curl);

        if (res != CURLE_OK)
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
        else
            printf("Email sent successfully!\n");

        // Cleanup
        curl_slist_free_all(recipients);
        curl_easy_cleanup(curl);
    }

    return (int)res;
}
