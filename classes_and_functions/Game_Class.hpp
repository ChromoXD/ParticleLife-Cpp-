#pragma once
#include <array>
#include <vector>
#include <raylib.h>

class Game{
    private:
        float time{0};
        int FPS;
        int score{0};
        int NOP;
    
    public:

        Game(int FPS, int NOP){
            SetTargetFPS(FPS);
            this->FPS = FPS;
            this->NOP = NOP;
            Particles.resize(NOP);

            InitParticle();
        }
        
        std::vector<int> Particles;
    
        void UpdateTime();
        void InitParticle();
        
        int getFPS(){return this->FPS;}
        float getTime(){return this->time;}
        void setFPS(int FPS){ this->FPS = FPS;}
        
        
        void Reset();
};