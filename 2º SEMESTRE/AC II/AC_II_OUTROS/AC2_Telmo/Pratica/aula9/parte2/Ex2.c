void setPWM(unsigned int dutyCycle){

    // duty_cycle must be in the range [0, 100]
    if(dutyCycle >= 0 && dutyCycle <= 100){
        // Determine OC1RS as a function of "dutyCycle"
        OC1RS = ((PR3 + 1) * dutyCycle) /100;
    }      

}