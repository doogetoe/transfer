#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char scanflogreturned[64]; // scanf return variable

typedef enum {
    EVENT_PRINTF,
    EVENT_PRINTF_TEXT,
    EVENT_SCANF
} EventType;

typedef struct {
    EventType type;
    int value; // for integer values
    char textprint[64]; // for text printing
} Event;

#define MAX_EVENTS 128
Event eventLog[MAX_EVENTS];
int eventCount = 0;

// game-side: add event to log
int log_event(Event e) {
    if (eventCount < MAX_EVENTS) {
        eventLog[eventCount++] = e;
    }
    return 1;
}

char* scanfloog() {
    static char buffer[64]; // buffer
    fgets(buffer, sizeof(buffer), stdin); // scanf but better
    return buffer; // it does what it says
}

// engine-side: apply ONE event
void engine_apply_event(Event e) {
    
    if (e.type == EVENT_PRINTF) {
        printf("%d\n", e.value); // print integer value
    } else if (e.type == EVENT_PRINTF_TEXT) {
        printf("%s\n", e.textprint); // print text, i should merge these two event types later
    } else if (e.type == EVENT_SCANF) {
        char *c = scanfloog(); // input function
        strncpy(scanflogreturned, c, 63); // copy to return variable
        scanflogreturned[sizeof(scanflogreturned) - 1] = '\0'; // last thingy get null terminated
    }
}


// engine-side: replay ALL events
void engine_replay() {
    for (int i = 0; i < eventCount; i++) {
        engine_apply_event(eventLog[i]);
    }
}

int main() {
    // game creates events
    log_event((Event){ EVENT_PRINTF, 10 });
    log_event((Event){ EVENT_PRINTF, 20 });
    log_event((Event){ EVENT_PRINTF, 30 });
    log_event((Event){EVENT_PRINTF_TEXT, 0, "hi\n"});
    log_event((Event){EVENT_SCANF, 0, ""});
    

    // engine replays them
    engine_replay();

    printf("Scanf returned: %s\n", scanflogreturned); //print result of scanf using scanf return variable
    
    return 0;
}
