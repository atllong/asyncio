#ifndef FDEVENTS_H
#define FDEVENTS_H

#include <stdint.h>

#define FDEVENT_EVENT_READ		(1 << 0)
#define FDEVENT_EVENT_WRITE		(1 << 1)
#define FDEVENT_EVENT_ERROR		(1 << 2)

#define FDEVENT_FLAG_NONE		0
#define FDEVENT_FLAG_CONTRACTOR		(1 << 0)
#define FDEVENT_FLAG_CANCELLABLE	(1 << 1)
#define FDEVENT_FLAG_ASYNCCANCEL	(1 << 2)

typedef void *fdevent_handle_t;
typedef void (*fdevent_callback)(int fd, uint16_t revents, void *arg, int *continued);

struct fdevent_info {
	int fd;
	uint16_t events;
	uint32_t flags;
	fdevent_callback cb;	/* Called when event occurs */
	void *arg;
};

#define fdevent_continue(continued)	(*(continued) = 1)

int fdevent_init(void);
int fdevent_register(struct fdevent_info *evinfo, fdevent_handle_t *handle);
int fdevent_join(fdevent_handle_t handle);
int fdevent_cancel(fdevent_handle_t handle);
int fdevent_acquire_handle(fdevent_handle_t handle);
void fdevent_release_handle(fdevent_handle_t handle);
void fdevent_cleanup(void);

#endif
