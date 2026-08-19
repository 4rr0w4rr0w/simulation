#include "display.h"
#include <stdio.h>

struct Particle{
   int color;
   float x;
   float y;
   float vecX;
   float vecY;
};


int main(void)
{
    const int width = 640;
    const int height = 480;    
    const int particle_count = 1000;
    struct Particle particles[particle_count];

    Display *display = display_create(width, height);
    uint32_t *pixels = display_pixels(display);

    for (int i = 0; i < particle_count; i++) {
	struct Particle *p = &particles[i];
	
	p->x = i%640;
	p->y = i%480;
	p->vecX = 0;
	p->vecY = 0;
	p->color = ((i*30)%256<<16)+((i*5)%256<<8)+((i%256));
	uint32_t *pixel_ref = &pixels[(uint32_t)p->y*width+(uint32_t)p->x];
	*pixel_ref += p->color;
    
    }

    if (!display)
        return 1;

    while (display_is_open(display)) {
	for(int i = 0; i < particle_count; i++){
	   struct Particle *p = &particles[i];
	   uint32_t *pixel_ref = &pixels[(uint32_t)p->y*width+(uint32_t)p->x];
	   uint32_t pixel = *pixel_ref;

	   uint8_t r = ( pixel & 0x00FF0000 ) >> 16;
	   uint8_t g = ( pixel & 0x0000FF00 ) >> 8;
	   uint8_t b = ( pixel & 0x000000FF );

	   uint8_t r1 = ( p->color & 0x00FF0000 ) >> 16;
	   uint8_t g1 = ( p->color & 0x0000FF00 ) >> 8;
	   uint8_t b1 = ( p->color & 0x000000FF );

	   *pixel_ref -= p->color;
	   
	   float dx = width / 2.0f - p->x;
	   float dy = height / 2.0f - p->y;

           p->vecX += dx;
	   p->vecY += dy;
	   p->vecX += ((p->x>(width/2))?-1:1);
	   p->vecY += ((p->y>(height/2))?-1:1);
	   
	   p->vecX *= 0.001f;
	   p->vecY *= 0.001f;

	   p->vecX += ((int)g1-(int)g)/40;
	   p->vecY += ((int)b1-(int)b)/40;
	   p->x += p->vecX;
	   p->y += p->vecY;

	   if(p->x>=width){
		p->x=width-1;
	   }else if (p->x<0){
	   	p->x=0;
	   }

	   if(p->y>=height){
		p->y=height-1;
	   }else if (p->y<0){
	   	p->y=0;
	   }
	   uint32_t *new_pixel = &pixels[(uint32_t)p->y*width+(uint32_t)p->x];
	   *new_pixel += p->color;
	}

        display_update(display);
    }

    display_destroy(display);

    return 0;
}
