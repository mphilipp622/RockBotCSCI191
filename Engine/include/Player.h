#ifndef PLAYER_H
#define PLAYER_H

#include <GL\GL.h>
#include <Model.h>
#include <TextureLoader.h>
#include <DeltaTime.h>
#include <AudioEngine.h>
#include <vector>
#include <cstdlib>
#include <time.h>
#include <Timer.h>
#include <ChordManager.h>

using namespace std;

typedef struct
{
    float x, y, z;
}vec1;

// class for player character. Inherits from Model for positions/rotations/etc.
class Player : public Model
{
    public:
        Player(double, double);
        virtual ~Player();

        float scaleSize[3] = {1.0, 1.0, 1.0}; // x, y, z scale values
        vec1 vertices[4]; // 4 vertices of xyz values

        // player stats


        void DrawPlayer();
        void InitPlayer();

        int actionTrigger;
        void Actions(int);

        void Update();

        // Character Controller Functions
        void Jump();
        void ShootProjectile(double x, double y);
        void StartJump();

        // x Movement
        void StartMove(float dir);
        void MoveLeft();
        void MoveRight();
        void StopMove();
        void SlowDown();

        void ApplyGravity();

        static Player* player;

        double GetOffsetX();
        double GetOffsetY();
        double GetZoom();

        // Set boolean flags for playing chords and initiate user input check
        void PlayChords(bool isPlaying);

        // Checks whether user presses the proper input or not. Note that userInput must match the inputs assigned in Player::icons vector
        void CheckUserInput(int userInput, LPARAM lParam);
        void TakeDamage(int damage);

        int getHP();

    protected:

    private:
        int hp;
        int moveSpeed, jumpSpeed;
        bool jump, slowDown, moving, playingChords, canPlay;
        float jumpVelocity, fallVelocity;
        float initialY;
        float xDirection, prevXDirection;
        float prevXPos, prevYPos;
        float acceleration, accelRate, maxAcceleration, deceleration;
        float gravity;
        float playerZoom;

        int chordDamage;

        vector<Model*> icons;
        int activeInput;
        Timer* chordTimer;
        double chordTimingWindow;
        double cooldownTargetTime;
        Timer* cooldownTimer;
        void NextInput();

        // music circle variables
        Model* musicCircle;
        bool drawCircle;
        Timer* circleTimer;

        // will use timer to check when we should stop drawing music circle
        void ToggleMusicCircle();
        void DrawMusicCircle();

        int idleFrame;
        Timer* frameTimer;
        TextureLoader run[4];
        TextureLoader idle[5];
        TextureLoader jumpAnim[4];

        bool CheckCollision();
        void CheckEnemyCollision();
        bool CheckCircleCollision();
        bool CheckCircleSquareCollision();

        void CheckHit();

        // Updates the positions of the input icons for chord playing. Also draws icons if chord button is held down. Called in Player whenever movements occur.
        void UpdateIcons();

        // Updates the canPlay boolean based on the cooldown timer
        void UpdateCooldownTimer();

        AudioSource* chord;
        ChordManager* chordManager;
};

#endif // PLAYER_H
