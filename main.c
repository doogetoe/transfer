#include <stdio.h>

typedef enum {
    EVENT_PRINTF,
    EVENT_PRINTF_TEXT
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
void log_event(Event e) {
    if (eventCount < MAX_EVENTS)
        eventLog[eventCount++] = e;
}

// engine-side: apply ONE event
void engine_apply_event(Event e) {
    if (e.type == EVENT_PRINTF) {
        printf("%d\n", e.value);
    } else if (e.type == EVENT_PRINTF_TEXT) {
        printf("%s\n", e.textprint);
        
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

    // engine replays them
    engine_replay();

    return 0;
}
