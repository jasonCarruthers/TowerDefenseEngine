#ifndef HFILE_PIXEL
#define HFILE_PIXEL


void SetPixel(int x, int y, const Color3 &color);
void RefreshScreen();

extern float *pixelBuffer;

#endif /*HFILE_PIXEL*/