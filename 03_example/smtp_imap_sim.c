#include <stdio.h>
#include <string.h>

#define MAX_MSG 1024

// Simulated email server storage
char mail_storage[MAX_MSG] = "";

// Simulate SMTP send
void smtp_send(const char *sender, const char *recipient, const char *message) {
    printf("SMTP SESSION STARTED\n");
    printf("HELO mail.example.com\n");
    printf("MAIL FROM:<%s>\n", sender);
    printf("RCPT TO:<%s>\n", recipient);
    printf("DATA\n%s\n.\n", message);

    // Store message on server
    snprintf(mail_storage, MAX_MSG, "From: %s\nTo: %s\nMessage: %s", sender, recipient, message);
    printf("250 OK: Message stored on server.\n\n");
}

// Simulate IMAP receive
void imap_fetch(const char *user) {
    printf("IMAP SESSION STARTED\n");
    printf("LOGIN %s\n", user);

    if (strlen(mail_storage) > 0) {
        printf("FETCH 1 BODY[]\n");
        printf("%s\n", mail_storage);
    } else {
        printf("No new messages.\n");
    }

    printf("LOGOUT\n\n");
}

int main() {
    const char *sender = "bob@gmail.com";
    const char *recipient = "alice@yahoo.com";
    const char *message = "Hi Alice, this is a test email using simulated SMTP and IMAP.";

    // Simulate sending email
    smtp_send(sender, recipient, message);

    // Simulate recipient fetching the email
    imap_fetch("alice@yahoo.com");

    return 0;
}
