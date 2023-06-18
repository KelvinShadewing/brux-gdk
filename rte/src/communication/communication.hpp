#ifndef COMMUNICATION_H
#define COMMUNICATION_H
#include "../math/rectangle2.hpp"
#include <vector>
#include "event_info.hpp"

class Communication{
    static bool MatchEvent(EventInfo a, EventInfo b);
    static bool AddEvent(EventInfo e);
    static bool RemoveEvent(EventInfo e);
    static std::vector<EventInfo> events;
};

#endif