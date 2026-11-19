#pragma once
#include <vector>
#include <array>
#include <cmath>

class Game{
    private:
        float time{0};
        int FPS;
        int score{0};

    public:
        int NOP;
        int ANOP;

        Game(int FPS, int NOP){
            this->FPS = FPS;
            this->NOP = NOP*2;
            this->ANOP = NOP;

            ParticlePos[0].resize(std::ceil(this->NOP/2));
            ParticlePos[1].resize(std::floor(this->NOP/2));
            Next_ParticlePos.resize(this->NOP);

            InitParticle();
        }
        
        std::array<std::vector<float>, 2> ParticlePos;
        std::vector<float> Next_ParticlePos;
    
        void UpdateTime();
        void InitParticle();
        
        int getFPS(){return this->FPS;}

        float getTime(){return this->time;}
        void setFPS(int FPS){ this->FPS = FPS;}
        
        
        void Reset();
};