#include "utils.h"

uint64_t uniqueId(uint16_t v1, uint16_t v2, uint16_t v3, uint16_t v4)
{ 
   uint64_t id;
   id = v1 | (((uint64_t)v2) << 16) | (((uint64_t)v3) << 32) | (((uint64_t)v4) << 48);
   return id;
}