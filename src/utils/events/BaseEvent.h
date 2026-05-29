#pragma once

#include "IEvent.h"
#include "IListener.h"
#include <vector>
#include <algorithm>

namespace CarbonLab {

    template <typename TPayload>
    class BaseEvent : public IEvent {
    public:
        virtual ~BaseEvent() = default;

        void subscribe(IListener<TPayload>& listener) {
            listeners.push_back(&listener);
            listener.setId(static_cast<unsigned int>(listeners.size()));
        }

        void unsubscribe(IListener<TPayload>* listener) {
            listeners.erase(
                std::remove(listeners.begin(), listeners.end(), listener),
                listeners.end()
            );
        }

        void raise(TPayload message) {
            for (auto* listener : listeners) {
                listener->onEvent(message);
            }
        }

    private:
        std::vector<IListener<TPayload>*> listeners;
    };
}