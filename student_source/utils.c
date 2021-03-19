#include "utils.h"

uint32_t hash(uint32_t mask, uint32_t tableSize)
{
   // in our case we have p = 32, so it is simply h = (2654435769 * k) % 2 ^ 32
   uint32_t knuth = 2654435769;
   return (mask * knuth) % tableSize;
}
/********************************************************************
 * Generate a netmask of length prefixLength
 ********************************************************************/
void getNetmask(int prefixLength, int *netmask)
{

   *netmask = (0xFFFFFFFF << (IP_ADDRESS_LENGTH - prefixLength));
   if (prefixLength == 0)
   {
      *netmask = 0x00;
   }
}

//RL Lab 2020 Switching UC3M
