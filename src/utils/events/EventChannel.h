#pragma once

#include "BaseEvent.h"
#include <memory>

namespace CarbonLab {

    template <class TInstance, typename TEventPayload>
    class EventChannel {
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

    protected:
        EventChannel(const BaseEvent<TEventPayload>& event) : event(std::make_shared<BaseEvent<TEventPayload>>(event)) {}
        
        std::shared_ptr<BaseEvent<TEventPayload>> event;
    };

}