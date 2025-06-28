#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <time.h>

#define MAX_INPUT 256
#define RESPONSE_COUNT 5

/* Structure to hold keyword-response pairs */
typedef struct {
    char *keyword;
    char *responses[RESPONSE_COUNT];
} BotResponse;

/* Greeting messages */
const char *greetings[] = {
    "Hello! How can I help you today?",
    "Hi there! What can I do for you?",
    "Greetings! How may I assist you?",
    "Hey! What's on your mind?",
    "Welcome! How can I be of service?"
};

/* Farewell messages */
const char *farewells[] = {
    "Goodbye! Have a great day!",
    "See you later!",
    "Farewell! Come back anytime.",
    "Bye bye! It was nice talking to you.",
    "Chat again soon!"
};

/* Bot responses database */
BotResponse responses[] = {
    {
        .keyword = "hello",
        .responses = {"Hello there!", "Hi!", "Hey!", "Greetings!", "Howdy!"}
    },
    {
        .keyword = "name",
        .responses = {"I'm SimpleBot!", "You can call me SimpleBot.", "My name is SimpleBot.", "I'm known as SimpleBot.", "SimpleBot at your service!"}
    },
    {
        .keyword = "hello",
        .responses = {"Hello there!", "Hi!", "Hey!", "Greetings!", "Howdy!"}
    },
    {
        .keyword = "how are you",
        .responses = {"I'm just a program, but I'm functioning well!", "Doing great, thanks for asking!", "All systems go!", "01001000 (That's binary for 'I'm good!')", "I'm fine, how about you?"}
    },
    {
        .keyword = "help",
        .responses = {"I can respond to simple questions.", "Try asking about my name, or just say hello!", "I'm a simple bot, but I'll do my best!", "My responses are limited, but I'm happy to chat!", "Ask me anything, but keep it simple!"}
    },
    {
        .keyword = "thank",
        .responses = {"You're welcome!", "My pleasure!", "Happy to help!", "No problem!", "Anytime!"}
    },
    {
        .keyword = "bye",
        .responses = {"Goodbye!", "See you later!", "Farewell!", "Bye bye!", "Talk to you soon!"}
    },
    {
        .keyword = "time",
        .responses = {"I don't actually know the time, sorry!", "Time is relative.", "My internal clock says NOW.", "Check your system clock!", "I'm timeless!"}
    },
    {
        .keyword = "joke",
        .responses = {"Why don't programmers like nature? Too many bugs!", "How many programmers does it take to change a light bulb? None, it's a hardware problem!", "Real programmers count from 0.", "Why was the JavaScript developer sad? He didn't know how to 'null' his feelings!"}
    }
};
int response_count = sizeof(responses) / sizeof(responses[0]);

/* Convert string to lowercase */
void to_lower_case(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

/* Get a random index for response arrays */
int get_random_index(int max) {
    return rand() % max;
}

/* Find and return a matching response */
const char *find_response(const char *input) {
    char input_copy[MAX_INPUT];
    strncpy(input_copy, input, MAX_INPUT);
    to_lower_case(input_copy);

    /* Check for special commands first */
    if (strstr(input_copy, "bye") || strstr(input_copy, "goodbye") || strstr(input_copy, "exit")) {
        return farewells[get_random_index(sizeof(farewells) / sizeof(farewells[0]))];
    }

    /* Check for greeting patterns */
    if (strstr(input_copy, "hi") || strstr(input_copy, "hello") || strstr(input_copy, "hey")) {
        return greetings[get_random_index(sizeof(greetings) / sizeof(greetings[0]))];
    }

    /* Check all other responses */
    for (int i = 0; i < response_count; i++) {
        if (strstr(input_copy, responses[i].keyword)) {
            return responses[i].responses[get_random_index(RESPONSE_COUNT)];
        }
    }

    /* Default response if nothing matches */
    static const char *default_responses[] = {
        "I'm not sure I understand. Could you rephrase that?",
        "Interesting... Could you tell me more?",
        "I don't have a response for that. Try asking something else.",
        "Sorry, I didn't get that.",
        "Could you clarify that?"
    };
    return default_responses[get_random_index(sizeof(default_responses) / sizeof(default_responses[0]))];
}

/* Main chat loop */
void chat_loop() {
    char input[MAX_INPUT];
    printf("SimpleBot: %s\n", greetings[get_random_index(sizeof(greetings) / sizeof(greetings[0]))]);
    printf("Type 'bye' or 'exit' to quit.\n");

    while (1) {
        printf("\nYou: ");
        if (!fgets(input, MAX_INPUT, stdin)) {
            break;
        }

        /* Remove newline character */
        input[strcspn(input, "\n")] = '\0';

        if (strlen(input) == 0) {
            printf("SimpleBot: Did you want to say something?\n");
            continue;
        }

        /* Exit condition */
        if (strcasecmp(input, "bye") == 0 || strcasecmp(input, "exit") == 0) {
            printf("SimpleBot: %s\n", find_response(input));
            break;
        }

        /* Get and print response */
        printf("SimpleBot: %s\n", find_response(input));
    }
}

int main() {
    /* Initialize random seed */
    srand(time(NULL));
    
    printf("=== SimpleBot Chat ===\n");
    printf("A basic C language chatbot\n");
    printf("----------------------------\n");

    chat_loop();

    return 0;
}
