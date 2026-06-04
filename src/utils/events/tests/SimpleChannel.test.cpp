#include "utils/events/Event.h"
#include <gtest/gtest.h>

using namespace CarbonLab;

struct PlayEventMessage {
    bool isPlaying;
};

class PlayEvent : public Event<PlayEventMessage> {};
class PlayEventListener : public Listener<PlayEventMessage> {

    void onEvent(PlayEventMessage payload) override {
        EXPECT_EQ(payload.isPlaying, true);
    }
};

TEST(EventTest, SimpleChannel) {
    PlayEvent event;
    PlayEventListener listener;

    EXPECT_EQ(listener.getId(), 0);
    event.subscribe(listener);
    EXPECT_EQ(listener.getId(), 1);

    PlayEventMessage message{true};
    event.raise(message);
}