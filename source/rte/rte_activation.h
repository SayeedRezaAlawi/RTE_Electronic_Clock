/**************************************************
 ** The RTE activation engine (autogenerated)
 **************************************************/

#ifndef RTE_ACTIVATION_H
#define RTE_ACTIVATION_H

#include "project.h"
#include "global.h"
#include "rte.h"


 /** 
 ** Global RTE event mask 
 **/ 
#define RTE_EVENTMASK 0 | ev_joystick_onUpdate | ev_engine_onUpdate

/** 
 ** Cyclic Activation Table
 **/ 
 extern const RTE_cyclicTable_t RTE_cyclicActivationTable[]; 
 extern const uint16_t RTE_cyclicActivation_size; 

/** 
 ** Event Activation Table
 **/ 
 extern const RTE_eventTable_t RTE_eventActivationTable[]; 
 extern const uint16_t RTE_eventActivation_size; 



#endif
