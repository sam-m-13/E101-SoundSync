#ifndef LISTENER_H
#define LISTENER_H

class Listener {
  private:
    int volumeMin;
    int volumeMax;
    int pitchMin;
    int pitchMax;
    int window;
    int frequency;
  public:
    static bool triggered;
    Listener(int vMin, int vMax, int pMin, int pMax, int w, int f);
    void tick(unsigned int sample);
};

#endif