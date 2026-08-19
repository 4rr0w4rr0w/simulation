#include "display.h"
#include <PixelToaster.h>

struct Display {
    PixelToaster::Display window;
    PixelToaster::TrueColorPixel* pixels;
    int width;
    int height;

    Display(int w, int h)
        : window("Background", w, h),
          pixels(new PixelToaster::TrueColorPixel[w * h]),
          width(w),
          height(h)
    {
    }

    ~Display()
    {
        delete[] pixels;
    }
};

Display* display_create(int width, int height)
{
    return new Display(width, height);
}

void display_destroy(Display* display)
{
    delete display;
}

uint32_t* display_pixels(Display* display)
{
    return reinterpret_cast<uint32_t*>(display->pixels);
}

int display_update(Display* display)
{
    return display->window.update(display->pixels) ? 1 : 0;
}

int display_is_open(Display* display)
{
    return display->window.open() ? 1 : 0;
}
