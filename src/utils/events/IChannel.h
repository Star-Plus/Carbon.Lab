#pragma once

#include "BaseEvent.h"

namespace CarbonLab {

    template <class TInstance, typename TEventPayload>
    class IChannel {
    public:
        TInstance* getInstance() {
            static TInstance instance;
            return &instance;
        }
        
        void push(const TEventPayload& payload) {
            event.raise(payload);
        }

        void subscribe(IListener<TEventPayload>& listener) {
            event.subscribe(listener);
        }

        void unsubscribe(IListener<TEventPayload>* listener) {
            event.unsubscribe(listener);
        }

    private:
        IChannel(const BaseEvent<TEventPayload>& event) : event(event) {}
        
        BaseEvent<TEventPayload> event;
    };

}