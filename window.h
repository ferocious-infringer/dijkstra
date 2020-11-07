#ifndef WINDOW_H
#define WINDOW_H

int window_create(void);
void window_loop(void);

void window_set_display(void (*)(void));
void window_set_idle(void (*)(void));
void window_redisplay(void);

#endif /* WINDOW_H */
