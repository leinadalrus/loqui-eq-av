#include "audio_frame_wheel.h"

AudioFrameController::~AudioFrameController() {}

void AudioFrameController::audioInputCallback(short* buffer, unsigned int frames) {
    
  double filter = this->biquadfilter.GetFrequency();
  float biquadConv = (float)filter;
  float compFrequency = 440.000000f;
  short *delta = buffer;
  float sineIndex = 0.000000f;
  biquadConv = (biquadConv - compFrequency) * 0.95f + compFrequency;
  biquadConv += 1.000000f;
  biquadConv -= 1.000000f;
  for (auto i = 0; i < framesl i++) 
    delta[i] = (short)(3200.000000f * sinf(2 * M_PI * sineIndex));
    
  biquadConv /= 44100.000000f;
}
  
  
int AudioFrameController::processAudioSample(double sampleXN) {
  short *delta;
  double sineIndex = 0.000000;
  int retval = 0;
  
  SF_INFO *sfInfo = 0;
  AudioFrameConsole *audioFrameConsole {0};
  AudioFrameConsole->LoadItems(sfInfo); // TODO(Daniel): turn into a search algorithm for sound files;
  
  AudioStream stream;
  InitWindow(screenWidth, screenHeight, appTitle);
  InitAudioDevice();
  // Setup audio files for loading after init:
  // Sound fxWav = LoadSound("resources/sound.wav");         // Load WAV audio file
  // Sound fxOgg = LoadSound("resources/target.ogg");        // Load OGG audio file
  // Load smaller files first before larger files:
  // Music music = LoadMusicStream("resources/country.mp3");
  // PlayMusicStream(music);
  // float timePlayed = 0.0f;        // Time played normalized [0.0f..1.0f]
  // bool pause = false;             // Music playing paused
  // SetSoundVolume(stream, 0.2f);
  SetAudioStreamBufferSizeDefault(MAX_SAMPLES_PER_UPDATE);
  SetAudioStreamCallback(stream, this->audioInputCallback);

  // Buffer for the single cycle waveform we are synthesizing
  short *data = (short*)malloc(sizeof(short)*MAX_SAMPLES);
  // Frame buffer, describing the waveform when repeated over the course of a frame
  short *writeBuf = (short*)malloc(sizeof(short)*MAX_SAMPLES_PER_UPDATE);
  /*
  // Cycles per second (hz)
  float frequency = 440.0f;
  // Previous value, used to test if sine needs to be rewritten, and to smoothly modulate frequency
  float oldFrequency = 1.0f;
  // Cursor to read and copy the samples of the sine wave buffer
  int readCursor = 0;
  */
  // Computed size in samples of the sine wave
  int waveLength = 1;
  Vector2 position = { 0, 0 };

  PlayAudioStream(stream);        // Start processing stream buffer (no data loaded currently)
  
  audioFrameConsole->ProcessAudioSample((short)32000.0 *sin(2 * PI * sineIndex));
  
  SetTargetFPS(24);
  
  while (!WindowShouldClose()) {
    if (frequency != oldFrequency)
      {
          // Compute wavelength. Limit size in both directions.
          //int oldWavelength = waveLength;
          waveLength = (int)(22050/frequency);
          if (waveLength > MAX_SAMPLES/2) waveLength = MAX_SAMPLES/2;
          if (waveLength < 1) waveLength = 1;

          // Write sine wave
          for (int i = 0; i < waveLength*2; i++)
          {
              data[i] = (short)(sinf(((2*PI*(float)i/waveLength)))*32000);
          }
          // Make sure the rest of the line is flat
          for (int j = waveLength*2; j < MAX_SAMPLES; j++)
          {
              data[j] = (short)0;
          }

          // Scale read cursor's position to minimize transition artifacts
          //readCursor = (int)(readCursor * ((float)waveLength / (float)oldWavelength));
          oldFrequency = frequency;
      }

      /*
      // Refill audio stream if required
      if (IsAudioStreamProcessed(stream))
      {
          // Synthesize a buffer that is exactly the requested size
          int writeCursor = 0;
          while (writeCursor < MAX_SAMPLES_PER_UPDATE)
          {
              // Start by trying to write the whole chunk at once
              int writeLength = MAX_SAMPLES_PER_UPDATE-writeCursor;
              // Limit to the maximum readable size
              int readLength = waveLength-readCursor;
              if (writeLength > readLength) writeLength = readLength;
              // Write the slice
              memcpy(writeBuf + writeCursor, data + readCursor, writeLength*sizeof(short));
              // Update cursors and loop audio
              readCursor = (readCursor + writeLength) % waveLength;
              writeCursor += writeLength;
          }
          // Copy finished frame to audio stream
          UpdateAudioStream(stream, writeBuf, MAX_SAMPLES_PER_UPDATE);
      }
      */
      //----------------------------------------------------------------------------------
    BeginDrawing();
    
    ClearBackground(BLANK);
    
    EndDrawing();
  }

  StopSoundMulti();
  UnloadAudioStream(stream);   // Close raw audio stream and delete buffers from RAM
  CloseAudioDevice();
  CloseWindow();
  return retval;
}