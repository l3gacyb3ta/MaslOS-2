#pragma once
#include <stdint.h>
#include <stddef.h>
//#include "../stubs.h"
#include "../heap/heap.h"

enum MessagePacketType : uint8_t
{
    NONE,
    GENERIC_DATA,
    GENERIC_MESSAGE,
    KEY_EVENT,
    MOUSE_EVENT,
    WINDOW_BUFFER_EVENT,
    WINDOW_CREATE_EVENT,
    WINDOW_DELETE_EVENT,
    WINDOW_GET_EVENT,
    WINDOW_SET_EVENT
};

// CONVO IDS FOR STANDARDIZED STUFF
#define CONVO_ID_WM_MOUSE_STUFF     0xFF000100
#define CONVO_ID_WM_KB_STUFF           0xFF000101

#define CONVO_ID_WM_WINDOW_UPDATE 0xFF000110


struct GenericMessagePacket
{
public:
    uint64_t Size;
    uint64_t FromPID;
    uint64_t ConvoID;
    uint8_t* Data;
    MessagePacketType Type;
    
    GenericMessagePacket(MessagePacketType type, uint8_t* data, uint64_t size);
    GenericMessagePacket* Copy();
    void Free();
    
    GenericMessagePacket(MessagePacketType type, uint8_t* data, uint64_t size, Heap::HeapManager* manager);
    GenericMessagePacket* Copy(Heap::HeapManager* manager);
    void Free(Heap::HeapManager* manager);
};