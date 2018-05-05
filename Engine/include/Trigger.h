#ifndef TRIGGER_H
#define TRIGGER_H
#include <string>

using namespace std;

class Trigger
{
    public:
        Trigger();
        Trigger(double newX, double newY, double newWidth, double newHeight, string newText, string newTag);
        virtual ~Trigger();

        double GetX();
        double GetY();
        double GetWidth();
        double GetHeight();

        string GetTag();
        string GetText();

    protected:

    private:
        string tag, text;
        double xPos, yPos, width, height;
};

#endif // TRIGGER_H
