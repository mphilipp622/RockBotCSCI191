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
#include <Trigger.h>
#include <SceneManager.h>
#include "freetype.h"
#include <Particles.h>
//#include <Projectile.h>

using namespace std;

// Dhanyu's struct for handling vertices
typedef struct
{
    float x, y, z;
}vec1;


// class for player character. Inherits from Model for positions/rotations/etc.
class Player : public Model
{
    public:
        // Constructor will take x and y positions
        Player(double newX, double newY);
        virtual ~Player();

        vec1 vertices[4]; // 4 vertices of xyz values

        ////////////////////
        // PLAYER STATS
        ////////////////////

        // Decrement hp from the player and set him to invincible temporarily.
        void TakeDamage(int damage);

        // Returns the player's current hit points.
        int getHP();

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
        void CheckUserInput(int userInput, double mouseX, double mouseY);

        // Will be called on by GLScene when loading happens. WIll push new triggers into the trigger vector so player knows where all triggers are in the scene.
        void AddTextTrigger(Trigger* newTrigger);

        // used by enemy projectiles to determine if player is invincible or not.
        bool IsInvincible();


    protected:

    private:
        int hp;
        int moveSpeed, jumpSpeed;
        bool jump, slowDown, moving, attacking, playingChords, canPlay, invincible, pushBack;
        float jumpVelocity, fallVelocity;
        float initialY;
        float xDirection, prevXDirection;
        float prevXPos, prevYPos;
        float acceleration, accelRate, maxAcceleration, deceleration, pushAccel, pushDecel;
        float gravity;
        float playerZoom;

        double invincibleTime;
        int invincibleFrame;
        Timer* invincibleTimer; // used for making player invincible temporarily after taking damage
        Timer* invincibleFrameTimer; // used for animating alpha transparency when hit
        void CheckInvincible(); // checks if the timer has run out on invincibility
        void SetInvincible(); // sets the player to be invincible. This will be called after taking damage from an enemy.

        int chordDamage;

        Model* inputIcon;
        unordered_map<int, string> iconNames;
        vector<Model*> icons;
        int activeInput;
        Timer* chordTimer;
        double chordTimingWindow;
        double cooldownTargetTime;
        int bpm, beatsPerInput; // used for calculating chordTimingWindow. Beats per input is how many beats should pass before a new input is randomized
        Timer* cooldownTimer;
        void NextInput();

        // music circle variables
        Model* musicCircle;
        bool drawCircle;
        Timer* circleTimer;

        // will use timer to check when we should stop drawing music circle
        void ToggleMusicCircle();
        void DrawMusicCircle();

        int idleFrame, attackFrame, dieFrame;
        Timer* frameTimer;
        TextureLoader run[4];
        TextureLoader idle[5];
        TextureLoader jumpAnim[4];
        TextureLoader attackAnim[4];
//        TextureLoader dieAnim[];

//        Particle* sparkParticles;


        //////////////////////
        // COLLISION FUNCTIONS
        //////////////////////

        bool CheckCollision();
        void CheckEnemyCollision();
        void CheckHealthPackCollision(); // Checks if player has touched a health pack
        void CheckTriggerCollision(); // Used for checking text trigger collision
        bool CheckCircleCollision();
        bool CheckCircleSquareCollision();
        bool OverlapTrigger(double min0, double max0, double min1, double max1);
        void CheckHit();

        void ConsumeHealthPack(Model* healthPack); // Adds HP to player and deletes healthpack from GLScene

        // Updates the positions of the input icons for chord playing. Also draws icons if chord button is held down. Called in Player whenever movements occur.
        void UpdateIcons();

        // Updates the canPlay boolean based on the cooldown timer. Starts input minigame again when cooldown timer is over.
        void UpdateCooldownTimer();

        // Pushes player back when getting hit by a melee enemy
        void PushBack();

        void StartPushBack(double direction); // pushes player back

        AudioSource* chord;
        ChordManager* chordManager;

        vector<Trigger*> textTriggers;

        ////////////
        // FREE TYPE
        ////////////

        string textToDisplay; // this will be set by CheckTriggerCollision() by grabbing the trigger's text value
        bool displayText; // flag for displaying text in Player::Update(). Will be set by CheckTriggerCollision() when player steps inside a text trigger
        freetype::font_data test1_font;
        void DisplayText(); // This function is called at the bottom of Player::Update(). It will be where freetype2::print is called

        //////////////////
        // SPARK PARTICLES
        //////////////////

        vector<Particles*> sparks; // container for the sparks. Allows multiple spark particles at once.
//        Particles* sparks;
};

#endif // PLAYER_H
