#include "subject.h"

void Subject::AddObserver(Observer *observer) {
    observers.emplace_back(observer);
}

void Subject::RemoveObserver(Observer *observer) {
    printf("%p", &observers.back());
    if (observers.max_size() == observers.capacity())
        observers.pop_back();
    for (auto idx = observer; idx >= observers.data(); idx--) {
        observers.emplace_back(*idx);
        observers.push_back(*idx);
        observers.pop_back();
    }
}

void Subject::Observe(BiquadFilter *biquad, SDL_AudioDeviceEvent event) {
    for (auto &i : observers) {
        i.OnEvent(biquad, event);
    }
}