    /**
    * \file reactionGame.h
    * \author Sayeed Reza Alawi
    * \date 03.12.19
*
* \brief Reaction Game Drivers.
*
* detailed description what the file does
*
* \note <notes>
* Programming rules (may be deleted in the final release of the file)
* ===================================================================
*
* 1. Naming conventions:
*    - Prefix of your module in front of every function and static data. 
*    - Scope _ for public and __ for private functions / data / types, e.g. 
*       Public:  void CONTROL_straightPark_Init();
*       Private: static void CONTROL__calcDistance();
*       Public:  typedef enum {RED, GREEN, YELLOW} CONTROL_color_t
*    - Own type definitions e.g. for structs or enums get a postfix _t
*    - #define's and enums are written in CAPITAL letters
* 2. Code structure
*    - Be aware of the scope of your modules and functions. Provide only functions which belong to your module to your files
*    - Prepare your design before starting to code
*    - Implement the simple most solution (Too many if then else nestings are an indicator that you have not properly analysed your task)
*    - Avoid magic numbers, use enums and #define's instead
*    - Make sure, that all error conditions are properly handled
*    - If your module provides data structures, which are required in many other files, it is recommended to place them in a file_type.h file
*	  - If your module contains configurable parts, is is recommended to place these in a file_config.h|.c file
* 3. Data conventions
*    - Minimize the scope of data (and functions)
*    - Global data is not allowed outside of the signal layer (in case a signal layer is part of your design)
*    - All static objects have to be placed in a valid linker sections
*    - Data which is accessed in more than one task has to be volatile and needs to be protected (e.g. by using messages or semaphores)
*    - Do not mix signed and unsigned data in the same operation
* 4. Documentation
*    - Use self explaining function and variable names
*    - Use proper indentation
*    - Provide Javadoc / Doxygen compatible comments in your header file and C-File
*    		- Every  File has to be documented in the header
*			- Every function parameter and return value must be documented, the valid range needs to be specified
*     		- Logical code blocks in the C-File must be commented
*    - For a detailed list of doxygen commands check http://www.stack.nl/~dimitri/doxygen/index.html 
* 5. Qualification
*    - Perform and document design and code reviews for every module
*    - Provide test specifications for every module (focus on error conditions)
*
* Further information:
*    - Check the programming rules defined in the MIMIR project guide
*         - Code structure: https://fromm.eit.h-da.de/intern/mimir/methods/eng_codestructure/method.htm
*         - MISRA for C: https://fromm.eit.h-da.de/intern/mimir/methods/eng_c_rules/method.htm
*         - MISRA for C++: https://fromm.eit.h-da.de/intern/mimir/methods/eng_cpp_rules/method.htm 
*
* \todo <todos>
* \warning <warnings, e.g. dependencies, order of execution etc.>
*
*  Changelog:\n
*  - <version; data of change; author>
*            - <description of the change>
*
* \copyright Copyright ©2016
* Department of electrical engineering and information technology, Hochschule Darmstadt - University of applied sciences (h_da). All Rights Reserved.
* Permission to use, copy, modify, and distribute this software and its documentation for educational, and research purposes in the context of non-commercial
* (unless permitted by h_da) and official h_da projects, is hereby granted for enrolled students of h_da, provided that the above copyright notice,
* this paragraph and the following paragraph appear in all copies, modifications, and distributions.
* Contact Prof.Dr.-Ing. Peter Fromm, peter.fromm@h-da.de, Birkenweg 8 64295 Darmstadt - GERMANY for commercial requests.
*
* \warning This software is a PROTOTYPE version and is not designed or intended for use in production, especially not for safety-critical applications!
* The user represents and warrants that it will NOT use or redistribute the Software for such purposes.
* This prototype is for research purposes only. This software is provided "AS IS," without a warranty of any kind.
**/


 
#ifndef RACTIONGAME_H
#define RACTIONGAME_H

/*****************************************************************************/
/* Global pre-processor symbols/macros and type declarations                 */
/*****************************************************************************/
#include "project.h"
#include "global.h"
#include "button.h"
#include "led.h"

//####################### Enumerations
/**
* \brief Enumerations. Use brief, otherwise the index won't have a brief explanation.
*
* Detailed explaination of the enumeration.
*/
 enum eGame_s{
  Is_Initial,    /**< \brief Is_Initial state */
  Is_WaitRandTime,     /**< \brief Is_WaitRandTime state */
  Is_ButtonPressed,     /**< \brief Is_ButtonPressed state */
  Is_GameEnd,     /**< \brief Is_GameEnd state */
} ;
typedef enum eGame_s eGame_s_t;

 enum Game_event{
  ev_button,    /**< \brief ev_button event */
  ev_timeout,     /**< \brief ev_timeout event */
  ev_tooslow,     /**< \brief ev_tooslow event */
} ;
typedef enum Game_event Game_event_t;

 enum Ticks_s{
  ReadTicks,    /**< \brief ReadTicks */
  ResetTicks,     /**< \brief ResetTicks */
  IncreaseTicks,     /**< \brief IncreaseTicks */
} ;
typedef enum Ticks_s Ticks_s_t;

//####################### Structures
/**
* \brief The purpose as well as the members of a structure have to be documented.
*
* Make clear what the structure is used for and what is the purpose of the members.
*/


// Wrapper to allow representing the file in Together as class
#ifdef TOGETHER

class RACTIONGAME
{
public:
};
#endif /* Together */

/*****************************************************************************/
/* Extern global variables                                                   */
/*****************************************************************************/

//The global Reaction Game objects
extern uint32 Time[10];
extern BUTTON_id_t RandomButton;
extern BUTTON_id_t PressedButton;
extern eGame_s_t GameState;
extern uint8 MaxRound;

/*****************************************************************************/
/* API functions                                                             */
/*****************************************************************************/

/**
 * Reaction Game Initialisation
 * @return RC_SUCCESS
 */
RC_t REACTIONGAME_Init();

/**
 * Run the reaction Game according to event.
 * @param Game_event_t game_event   - type of event
 * @return RC_SUCCESS
 */
RC_t REACTIONGAME_Run(Game_event_t game_event);

/**
 * Increament the round turn.
 * @return Round
 */
uint8 REACTIONGAME_Round_Increament();

/**
 * Generats random time and enbles the ev_TimeOut event.
 * @return random number between 1 to 3 seconds.
 */
uint32 REACTIONGAME_RandTime();

/**
 * Generats random number of button and display on seven segment.
 * @return RC_SUCCESS
 */
RC_t REACTIONGAME_RandButtonSelect();

/**
 * Checks if the valid button is pressed.
 * @return RC_SUCCESS
 */
RC_t REACTIONGAME_CheckValidButton();

/**
 * Checks if player is too slow.
 * @return RC_SUCCESS
 */
RC_t REACTIONGAME_TooSlowPressed();

/**
 * Display the score on the console.
 * @return RC_SUCCESS
 */
RC_t REACTIONGAME_ShowScore();

/**
 * Display average time after 10 rounds.
 * @return RC_SUCCESS
 */
RC_t REACTIONGAME_ShowAvgTime();

/**
 * Increament the score.
 * @return RC_SUCCESS
 */
RC_t REACTIONGAME_IncreaseScore();

/**
 * Decreament the score.
 * @return RC_SUCCESS
 */
RC_t REACTIONGAME_DecreaseScore();

/**
 * Checks if the game is ended.
 * @return TRUE or FALSE
 */
boolean_t REACTIONGAME_CheckGameEnd();

/**
 * 1 ms Counter.
 * @return current counter value.
 */
uint32 REACTIONGAME_CounterTicks(Ticks_s_t ticks);

/**
 * Reads the counter value.
 * @return current counter value.
 */
uint32 REACTIONGAME_CounterTicks_Read();

/**
 * Resets the counter value.
 * @return RC_SUCCESS
 */
RC_t REACTIONGAME_CounterTicks_Reset();

/**
 * Increament the counter value.
 * @return RC_SUCCESS
 */
RC_t REACTIONGAME_CounterTicks_Increase();


#ifdef TOGETHER

};
#endif /* Together */

#endif /* FILE_H */
