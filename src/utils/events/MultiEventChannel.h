#pragma once

#include <map>
#include <memory>
#include "EventChannel.h"

namespace CarbonLab {
    template <class TInstance, class EventType>
    class MultiEventChannel {
    public:

        TInstance* getInstance() {
            static TInstance instance;
            return &instance;
        }

        template <typename TEventPayload>
        void push(const TEventPayload& payload, const EventType& type) {
            channels[type]->push(payload);
        }
        
        void subscribe(const IListener& listener, const EventType& type) {
            channels[type]->subscribe(listener);
        }

        void unsubscribe(const IListener* listener, const EventType& type) {
            channels[type]->unsubscribe(listener);
        }

    protected:

        template <typename TEventPayload>
        void addChannel(const EventType& type) {
            channels[type] = std::make_shared<EventChannel<TInstance, TEventPayload>>(Event<TEventPayload>());
        }

        void removeChannel(const EventType& type) {
            channels.erase(type);
        }

    private:
        std::map<EventType, std::shared_ptr<IEventChannel>> channels;
    };
}