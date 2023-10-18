#include "defs.h"

void initHunter(HunterType** hunter, char* name, RoomType* room, JournalType* journal) {
    *hunter = (HunterType*) malloc(sizeof(HunterType));
    strcpy((*hunter)->name, name);
    (*hunter)->room = room;
    (*hunter)->journal = journal;
    (*hunter)->fear = 0;
    (*hunter)->boredom = 0;
}

void* hunterThread(void* arg) {
    HunterType* hunter = (HunterType*) arg;
    // logAction(hunter->journal, hunter->name, "enters the building.");
    while (1) {
        slowThread();

        // Check if the hunter should exit
        if (hunter->fear >= MAX_FEAR || hunter->boredom >= MAX_BOREDOM) {
            // logAction(hunter, hunter->name, "exits the building.");
            pthread_exit(NULL);
        }

        // Increment boredom counter and check for ghost
        hunter->boredom++;
        if (hunter->room->ghost != NULL) {
            hunter->fear++;
            // logAction(hunter->journal, hunter->name, "spotted the ghost!");
        }
    }
}
