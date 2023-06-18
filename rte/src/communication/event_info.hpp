#ifndef EVENT_INFO_H
#define EVENT_INFO_H
#include <string>

class EventInfo{
    std::string event;
    std::string emitter_type;
    std::string receiver_type;
    int emitter_id;
    int receiver_id;
};

#endif