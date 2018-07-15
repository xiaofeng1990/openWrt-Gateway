#ifndef __THREAD_SCENE_H_
#define __THREAD_SCENE_H_
#include <stdio.h>
#include "gw_config.h"

void *scene_thread_f(void *parameter);
int scene_thread_init(struct tGatewayInfo *gatewayInfo);
void scene_thread_wait(struct tGatewayInfo *gatewayInfo);

#endif /* __THREAD_SCENE_H_ */



