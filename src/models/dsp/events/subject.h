#include "observer.h"
#include "events.h"
#include <vector>

#ifndef F1246265_60F6_45C8_AE16_4C996DFE511E
#define F1246265_60F6_45C8_AE16_4C996DFE511E

class Subject {
public:
    Observer *GetObserver() {
        return observer;
    }

    std::vector<Observer> GetObservers() {
        return observers;
    }

    void AddObserver(Observer *observer);
    
    void RemoveObserver(Observer *observer);
    // Soft-copy of classes for first parameter, events on second parameter:
    void Observe(BiquadFilter *biquad, SDL_AudioDeviceEvent event);

private:
    std::vector<Observer> observers;
    Observer *observer; // observer instance for check-validation
};

#endif /* F1246265_60F6_45C8_AE16_4C996DFE511E */
