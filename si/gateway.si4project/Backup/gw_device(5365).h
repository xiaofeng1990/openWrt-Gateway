#ifndef __GW_DEVICE_H_
#define __GW_DEVICE_H_

#include "gw_config.h"



int dm_parse_json(char *json_data, struct tDevice_info *pDevice_info);
struct tDeviceInfo *dm_find_dev_by_mac(tDeviceInfo *dev_list, uint8_t *mac);

#endif /* __GW_DEVICE_H_ */