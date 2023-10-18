#include "defs.h"

/* 
    Function: populateBuilding
    Purpose: Populates a building with rooms and doors
    Parameters: 
        in-out: BuildingType* building: The building to populate
    Returns: void
*/
void populateBuilding(BuildingType* building) {
    /*
        * Requires that the building has been initialized with initBuilding()
        * Requires that initRoom and connectRooms have been implemented
        * You are allowed to modify this function, but the room connections
        * must remain the same. The overall map MUST be the same, with the same names
        * and the same connections. Failure to do so will result in major
        * deductions.
    */

    // Room names array
    char* room_names[] = {
        "Van", "Hallway N", "Hallway S", "Master Bedroom", "Boy's Bedroom", "Bathroom",
        "Kitchen", "Living Room", "Garage", "Utility Room"
    };
    int num_rooms = sizeof(room_names) / sizeof(room_names[0]);

    // Initialize rooms: It should be strcpy/strlcpy/strncpy the name
    for (int i = 0; i < num_rooms; i++) {
        initRoom(&(building->rooms[i]), room_names[i]);
    }

    // Connect rooms. The first room, in the direction, you will find the second room.
    // connectRooms() returns a pointer to the door that connects the two rooms.
    building->doors[0] = connectRooms(building->rooms[0], SOUTH, building->rooms[1]);
    building->doors[1] = connectRooms(building->rooms[1], EAST, building->rooms[4]);
    building->doors[2] = connectRooms(building->rooms[1], WEST, building->rooms[3]);
    building->doors[3] = connectRooms(building->rooms[1], SOUTH, building->rooms[2]);
    building->doors[4] = connectRooms(building->rooms[2], EAST, building->rooms[5]);
    building->doors[5] = connectRooms(building->rooms[2], SOUTH, building->rooms[6]);
    building->doors[6] = connectRooms(building->rooms[6], SOUTH, building->rooms[7]);
    building->doors[7] = connectRooms(building->rooms[6], WEST, building->rooms[8]);
    building->doors[8] = connectRooms(building->rooms[8], NORTH, building->rooms[9]);

    building->roomCount = num_rooms;
    building->doorCount = 9;
}



/* 
    Function: initBuilding
    Purpose: initialize the building
    Parameters: 
        in-out: BuildingType** building: The building to initiate
    Returns: void
*/
void initBuilding(BuildingType** building) {
    *building = malloc(sizeof(BuildingType));
    (*building)->journal = NULL;
    (*building)->ghost = NULL;
    for (int i = 0; i < MAX_HUNTERS; i++) {
        (*building)->hunters[i] = NULL;
    }
    for (int i = 0; i < MAX_ROOMS; i++) {
        (*building)->rooms[i] = NULL;
    }
    for (int i = 0; i < MAX_DOORS; i++) {
        (*building)->doors[i] = NULL;
    }
    (*building)->doorCount = 0;
    (*building)->roomCount = 0;
    (*building)->hunterCount = 0;
}


void initRoom(RoomType** room, char* name) {
    // Dynamically allocate memory for the room
    *room = (RoomType*) malloc(sizeof(RoomType));

    // Set default values for the room's fields
    strncpy((*room)->name, name, MAX_STR);
    (*room)->ghost = NULL;
    (*room)->evidence = NULL;
    (*room)->hunterCount = 0;

    for (int i = 0; i < MAX_HUNTERS; i++) {
        (*room)->hunters[i] = NULL;
    }
    for (int i = 0; i < DIRECTION_COUNT; i++) {
        (*room)->doors[i] = NULL;
    }

    // Initialize the room's semaphore
    // sem_init(&((*room)->mutex), 0, 1);
}

void initDoor(DoorType** door, RoomType* roomA, RoomType* roomB) {
    // Dynamically allocate memory for the door
    *door = (DoorType*) malloc(sizeof(DoorType));
    if (*door == NULL) {
        // handle memory allocation failure
        return;
    }

    // Set default values for the door's fields
    (*door)->roomA = roomA;
    (*door)->roomB = roomB;

    // Initialize the door's semaphore
    // sem_init(&((*door)->mutex), 0, 1);
}

/* 
    Function: connectRooms
    Purpose:    take a room and a direction and another room, then initialize a door between those two rooms 
                and place them in the appropriate position in each room's doors array
    Parameters: 
        in-out: BuildingType** building: The building to initiate
    Returns: void
*/
DoorType* connectRooms(RoomType* roomA, DirectionType direction, RoomType* roomB) {
    // Dynamically allocate memory for the door
    DoorType* door = (DoorType*) malloc(sizeof(DoorType));

    // Set default values for the door's fields
    door->roomA = roomA;
    door->roomB = roomB;

    // Initialize the door's semaphore
    // sem_init(&(door->mutex), 0, 1);

    // Set the appropriate door in roomA and roomB to point to this door
    switch (direction) {
        case NORTH:
            roomA->doors[NORTH] = door;
            roomB->doors[SOUTH] = door;
            break;
        case EAST:
            roomA->doors[EAST] = door;
            roomB->doors[WEST] = door;
            break;
        case SOUTH:
            roomA->doors[SOUTH] = door;
            roomB->doors[NORTH] = door;
            break;
        case WEST:
            roomA->doors[WEST] = door;
            roomB->doors[EAST] = door;
            break;
        case DIRECTION_COUNT:
            break;
    }

    return door;
}

void initEvidence(EvidenceType **evidence, EvidenceCategoryType type, RoomType *origin) {
    // Allocate memory for the evidence
    *evidence = (EvidenceType *)malloc(sizeof(EvidenceType));

    // Set default values for the evidence fields
    (*evidence)->type = type;
    (*evidence)->founder = NULL;
    (*evidence)->origin = origin;
}


void initJournal(JournalType **journal) {
    *journal = malloc(sizeof(JournalType));

    (*journal)->head = NULL;
    (*journal)->size = 0;
    (*journal)->guess = UNKNOWN_GHOST;
    (*journal)->banished = 0;
    // sem_init(&((*journal)->mutex), 0, 1);
}

