#pragma once

#include "Event.h"
#include <memory>

namespace CarbonLab {

    class IEventChannel {
    };

    template <class TInstance, typename TEventPayload>
    class EventChannel : public IEventChannel {
    public:
        TInstance* getInstance() {
            static TInstance instance;
            return &instance;
        }
        
        void push(const TEventPayload& payload) {
            event.raise(payload);
        }

        void subscribe(Listener<TEventPayload>& listener) {
            event.subscribe(listener);
        }

        void unsubscribe(Listener<TEventPayload>* listener) {
            event.unsubscribe(listener);
        }

    protected:
        EventChannel(const Event<TEventPayload>& event) : event(std::make_shared<Event<TEventPayload>>(event)) {}
        
        std::shared_ptr<Event<TEventPayload>> event;
    };
}