#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct Display Display;

Display *display_create(int width, int height);
void display_destroy(Display *display);

uint32_t *display_pixels(Display *display);

int display_update(Display *display);
int display_is_open(Display *display);

#ifdef __cplusplus
}
#endif

#endif
