#include "defs.h"

int main() {
    // Seed the random number generator
    srand(time(NULL));
    // GhostType** ghost;
    // RoomType* room;
    // initGhost(ghost,room);
    // Your code below here!
    BuildingType* building;
    initBuilding(&building);

    // Populate the building with rooms and doors
    populateBuilding(building);

    // Initialize a journal and add it to the building
    JournalType* journal;
    initJournal(&journal);


    GhostType* ghost;
    initGhost(&ghost, building->rooms[rand() % 10]);
    pthread_join(ghost->thread, NULL);
    


  

    // Use the building and the journal in the game
    // ...

    // Free the memory allocated for the building and the journal
    // freeBuilding(building);
    // freeJournal(journal);

    return 0;
}