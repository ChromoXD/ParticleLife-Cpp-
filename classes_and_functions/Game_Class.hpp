#pragma once
#include <vector>

class Game{
    private:
        int FPS;

    public:
        int NOP, ANOP;

        Game(int FPS, int NOP){
            this->FPS = FPS;
            this->NOP = NOP*2;
            this->ANOP = NOP;

            ParticlePos.resize(this->NOP);
            InitParticle();
        }
        
        std::vector<float> ParticlePos;

        int getFPS(){return this->FPS;}
        
        void InitParticle();
        void setFPS(int FPS){ this->FPS = FPS;}
};