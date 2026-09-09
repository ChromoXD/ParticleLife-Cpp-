#pragma once
#include <array>
#include <vector>
#include <raylib.h>


class Game{
    private:
        float time{0};
        int FPS;
        int score{0};

    public:
        int NOP;

        Game(int FPS, int NOP){
            SetTargetFPS(FPS);
            this->FPS = FPS;
            this->NOP = NOP*2;
            ParticlePos.resize(this->NOP);
            Next_ParticlePos.resize(this->NOP);

            InitParticle();
        }
        
        std::vector<float> ParticlePos;
        std::vector<float> Next_ParticlePos;
    
        void UpdateTime();
        void InitParticle();
        
        int getFPS(){return this->FPS;}

        float getTime(){return this->time;}
        void setFPS(int FPS){ this->FPS = FPS;}
        
        
        void Reset();
};