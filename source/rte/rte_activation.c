/**************************************************
 ** The signal blackboard (autogenerated)
 **************************************************/

#include "project.h"
#include "global.h"
#include "rte.h"
#include "rte_activation.h" 


/* Software components */
#include "swc_application.h"
#include "swc_control.h"
#include "swc_engine.h"
#include "swc_joystick.h"
#include "swc_brakelight.h"
#include "swc_lcd.h"


/* Cyclic Table */

const RTE_cyclicTable_t RTE_cyclicActivationTable[] = { 
   { run_readJoystick, 1000 },
   
}; 

 const uint16_t RTE_cyclicActivation_size = sizeof (RTE_cyclicActivationTable) / sizeof(RTE_cyclicTable_t); 

/* Event Table */

const RTE_eventTable_t RTE_eventActivationTable[] = { 
   { run_calculateControl, ev_joystick_onUpdate },
   { run_setEngine, ev_engine_onUpdate },
   { run_setBrakeLight, ev_engine_onUpdate },
   { run_setLcd, ev_engine_onUpdate },
}; 

 const uint16_t RTE_eventActivation_size = sizeof (RTE_eventActivationTable) / sizeof(RTE_eventTable_t);
