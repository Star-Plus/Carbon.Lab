#pragma once

namespace CarbonLab {
    template <typename TPayload>
    class IListener {
    public:
        virtual ~IListener() {}

        virtual void onEvent(TPayload payload) = 0;

        unsigned int getId() const { return id_; }
        void setId(unsigned int id) { id_ = id; }
    private:
        unsigned int id_ = 0;
    };

}