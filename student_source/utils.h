#include <stdint.h>

/********************************************************************
 * Constant definitions
 ********************************************************************/
#define IP_ADDRESS_LENGTH 32


uint32_t hash(uint32_t mask, uint32_t  tableSize);
/********************************************************************
 * Generate a netmask of length prefixLength
 ********************************************************************/
void getNetmask (int prefixLength, int *netmask);

//RL Lab 2020 Switching UC3M
