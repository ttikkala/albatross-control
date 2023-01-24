// FIR class with ring buffer property
# include "RingBuffer.h"

class FIR {

private:
    float * coefficients;
    RingBuffer<float> ringBuffer;

public:
    // inherit size from coeff array?c
    FIR(size_t size, float coeffs[]) : coefficients(new float[size]), ringBuffer(size) {

        coefficients = coeffs;
    }

    float filter(float);


};


// Method to implement FIR filter on signal
// Array of input signals are convolved with an FIR filter coefficients array,
// the products of multiplication are summed together which gives the new, filtered output signal
float FIR::filter(float input) {

    // pointer to array of FIR coefficients, this will loop forwards though coeff array
    const float* coeff = this->coefficients;

    // add new input data to ring buffer
    this->ringBuffer.add(input);

    // create new output variable: this is the summation that will be returned 
    // at the end of the method
    float output = 0;

    // loop through buffer backwards starting from head of RB
    // loop through coefficients forwards from 0
    for(size_t i = this->ringBuffer.capacity; i > 0; i--) {
        output += this->ringBuffer.get(i) * *coeff++;
    }

    return output;

};

int main() {
    float coeffArray[51] = {-1.24904728523265e-18,	-0.00105623580106525,	-0.000769341020163074,
                            0.000956323223722641,	0.00197608274212223,	-2.62069141226653e-18,
                            -0.00326538480034455,	-0.00256851985290131,	0.00323463313088964,
                            0.00651990807521293,	-6.21170235731039e-18,	-0.00982573911486747,
                            -0.00736568540541010,	0.00888134892498642,	0.0172560569894422,
                            -1.06504359933304e-17,	-0.0247842716987335,	-0.0184176667681306,
                            0.0222995342882779,	    0.0442224438809103,	    -1.42414469383742e-17,
                            -0.0714698092268604,	-0.0604303288160902,	0.0923176269532090,
                            0.302027315266443,	    0.400523418058701,	    0.302027315266443,
                            0.0923176269532090,	    -0.0604303288160902,    -0.0714698092268604,
                            -1.42414469383742e-17,	0.0442224438809103,	    0.0222995342882779,
                            -0.0184176667681306,	-0.0247842716987335,	-1.06504359933304e-17,
                            0.0172560569894422,	    0.00888134892498642,	-0.00736568540541010,
                            -0.00982573911486747,	-6.21170235731039e-18,	0.00651990807521293,
                            0.00323463313088964,	-0.00256851985290131,	-0.00326538480034455,
                            -2.62069141226653e-18,	0.00197608274212223,	0.000956323223722641,
                            -0.000769341020163074,	-0.00105623580106525,	-1.24904728523265e-18};

    FIR FIRfilter(51, coeffArray);

    for(size_t i = 0; i < 10; i++) {
        for(size_t j = 0; j < 50; j++) {
            float y;

            if(i % 2 == 0) {
                y = 1;
            } else {
                y = -1;
            }

            float out = FIRfilter.filter(y);
            std::cout << out << ",";
        }
    }

    return 0;
};