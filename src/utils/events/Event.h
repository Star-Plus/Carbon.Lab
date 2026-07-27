#pragma once

#include "IEvent.h"
#include "Listener.h"
#include <vector>
#include <algorithm>
#include "CarbonExport.h"

namespace CarbonLab {

    template <typename TPayload>
    class Event : public IEvent {
    public:
        virtual ~Event() = default;

        void subscribe(Listener<TPayload>& listener) {
            listeners.push_back(&listener);
            listener.setId(static_cast<unsigned int>(listeners.size()));
        }

        void unsubscribe(Listener<TPayload>* listener) {
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
        std::vector<Listener<TPayload>*> listeners;
    };
}