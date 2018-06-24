#ifndef __GW_DEVICE_H_
#define __GW_DEVICE_H_

#include "gw_config.h"



int dm_add_device(char *json_data, struct tGatewayInfo *gatewayInfo);
struct tDeviceInfo *dm_find_dev_by_mac(tDeviceInfo *dev_list, uint8_t *mac);

#endif /* __GW_DEVICE_H_ */