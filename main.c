#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char scanflogreturned[64];

typedef enum {
    EVENT_PRINTF,
    EVENT_PRINTF_TEXT,
    EVENT_SCANF
} EventType;

typedef struct {
    EventType type;
    int value;
    char textprint[64];
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
    static char buffer[64];
    fgets(buffer, sizeof(buffer), stdin);
    return buffer;
}

// engine-side: apply ONE event
void engine_apply_event(Event e) {
    
    if (e.type == EVENT_PRINTF) {
        printf("%d\n", e.value);
    } else if (e.type == EVENT_PRINTF_TEXT) {
        printf("%s\n", e.textprint);
    } else if (e.type == EVENT_SCANF) {
        char *c = scanfloog();
        strncpy(scanflogreturned, c, 63);
        scanflogreturned[sizeof(scanflogreturned) - 1] = '\0';
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

    printf("Scanf returned: %s\n", scanflogreturned);
    
    return 0;
}
