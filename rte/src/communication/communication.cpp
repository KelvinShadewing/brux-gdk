#include "communication.hpp"
#include "event_info.hpp"

bool
Communication::MatchEvent(EventInfo a){
    for(auto b : events){
        if(a.event != ""){
            if(a.event != b.event) return false;
        }
        if(a.emitter_type != ""){
            if(a.emitter_type != b.emitter_type) return false;
        }

        if(a.receiver_type != ""){
            if(a.receiver_type != b.receiver_type) return false;
        }

        if(a.emitter_id != -1){
            if(a.emitter_id != b.emitter_id) return false;
        }

        if(a.receiver_id != -1){
            if(a.receiver_id != b.receiver_id) return false;
        }
        
        return true;
    }
    return false;
}