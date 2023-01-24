#include <Arduino.h>
#include <ArduinoJson.h>

struct PIDtuning
{
    float Kp;
    float Ki;
    float Kd;
    float antiwindup;
};

class PID{

    private:
        float setpt; 
        float currentError;
        float prevError;
        float prevUpdateTime;
        float integrator;
        float pError;
        float iError;
        float dError;
        float deltaT;

    public:
        PIDtuning tuning;
        PID(PIDtuning);
        void update(float);
        float getSetpt();
        void setSetpt(float);
        void calcpError();
        void calciError();
        void calcdError();
        void updateDeltaT(unsigned long);
        float output();
        float antiwindup(int, int);
        void outputJson();


};

PID::PID(PIDtuning tuneInput){
    tuning = tuneInput;
};

void PID::update(float input){
    this->prevError = this->currentError;
    this->currentError = input - this->setpt;

    unsigned long currentTime = millis();
    this->updateDeltaT(currentTime);
    this->prevUpdateTime = currentTime;
};

float PID::getSetpt(){
    return this->setpt;
};

void PID::setSetpt(float setpt){
    this->setpt = setpt;
    this->integrator = 0;
};

void PID::updateDeltaT(unsigned long currentTime){
    this->deltaT = currentTime - this->prevUpdateTime;
};

void PID::calcpError(){
    this->pError = this->currentError * (- this->tuning.Kp);
};

void PID::calciError(){
    this->integrator += this->currentError;
    this->iError = this->integrator * this->deltaT / this->tuning.Ki;
};

void PID::calcdError(){
    this->dError = (this->currentError - this->prevError) / this->deltaT;
};

float PID::output(){
    this->calcpError();
    this->calciError();
    this->calcdError();
    float error = this->pError + this->iError + this->dError;
    return error;
};


float PID::antiwindup(int highlim, int lowlim){
    float error = this->output();

    if (error >= highlim)
    {
        error = highlim;
        this->integrator += this->tuning.antiwindup * this->currentError;
    }
    else if (error <= lowlim)
    {
        error = lowlim;
        this->integrator += this->tuning.antiwindup * this->currentError;
    }

    return error;
};

// FIR filter

// Add debug method to return either JSON or data structure
void PID::outputJson(){
    const int capacity = JSON_OBJECT_SIZE(7);
    StaticJsonDocument<capacity> doc;

    doc["currentError"] = this->currentError;
    doc["prevError"] = this->prevError;
    doc["integrator"] = this->integrator;
    doc["pError"] = this->pError;
    doc["iError"] = this->iError;
    doc["dError"] = this->dError;
    doc["deltaT"] = this->deltaT;

    serializeJson(doc, Serial);
};

// Consider including pin logic

