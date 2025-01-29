// #pragma once

// #include "../lib/Task.h"
// #include "Motor.h"
// #include "Leg.h"
// //#include "Head.h"
// //#include "Torso.h"
// #include <set>

// class Movement : public Task {
//     public:
//         Movement(): Task("Task Movement"){
//             Motor * leg1 = new LeftLeg();
//             Motor * leg2 = new RightLeg();
//             //Motor * Torso = new Torso();
//             //Motor * Head = new Head();

//             motors.add(leg1);
//             motors.add(leg2);
//             //motors.add(Torso);
//             //motors.add(Head);

//             //interrupt initialisation for torso
//             // Configure the pin as an input
//             //pinMode(ioMapping::TORSO_INT, INPUT_PULLUP); 

//             // Attach the interrupt to the pin
//             //attachInterrupt(digitalPinToInterrupt(INTERRUPT_PIN), handleInterrupt, FALLING);

//         }

//         ~Movement(){
//             for(Motor * m : motors){
//                 delete m;
//             }
//         }

//         void task() override{
//             while(1){

//                 for(Motor * m : motors)
//                 {
//                     //m.move();
//                 }

//                 printf("Movement Task\n");
//                 vTaskDelay(pdMS_TO_TICKS(500));
//             }
//         }
//         void IRAM_ATTR handleInterrupt() {
//             // This is the ISR (Interrupt Service Routine)
//             motors[3]->stop(); //stop the torso motor
//         }
//     private:
//         std::set<Motor> motors;
        
// };

