#ifndef RANDUTILS_H
#define RANDUTILS_H

class RandFloat {
    public:
        RandFloat();
        /**
         * @brief Return a random number between 0 and 1
         * 
         * @return float 
         */
        float nextFloat();
    
    private:
        float x;
};



#endif