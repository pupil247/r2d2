/**
 * @file      controleMoteurs.cpp
 * @authors   Antoine Arbour, Félix Parent
 * @brief     Tâche et méthode de contrôle moteur
 * @date      07/05/2024 
 * @version   0.1
 * @mainpage  Echec_Math_S3 
*/

#include "Movement.h"
#include "esp_err.h"

volatile bool flagInt0, flagInt1;
volatile bool flagOutOfBounds_X, flagOutOfBounds_Y; 




struct moveInStep_t {
  uint16_t to[2];
  uint16_t from[2];
};

moveInStep_t moveInStep;

//bool IRAM_ATTR Timer0_ISR(void* arg){
  