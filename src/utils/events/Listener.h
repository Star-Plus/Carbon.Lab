#pragma once

#include "IListener.h"
namespace CarbonLab {
    template <typename TPayload>
    class Listener : public IListener {
    public:
        virtual ~Listener() {}

        virtual void onEvent(TPayload payload) = 0;

        unsigned int getId() const { return id_; }
        void setId(unsigned int id) { id_ = id; }
    private:
        unsigned int id_ = 0;
    };

}