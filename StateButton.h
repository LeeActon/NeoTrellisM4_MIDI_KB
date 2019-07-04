#include "Button.h"

class StateButton : public Button
    {
    protected:
    int state;
    int states;
    long int *colors;
    
    public:
    StateButton(int states, int state = 0, long int *colors = NULL)
        {
        this->states = states;
        this->state = state;
        this->colors = colors;
        }

    int GetState()
        {
        return this->state;
        }

    void SetColors(long int *colors)
        {
        this->colors = colors;
        }

    virtual void Press()
        {
        this->state++;
      
        if (this->state >= this->states)
          this->state = 0;

        if (this->colors != NULL)
            SetColor(this->colors[this->state]);
        }
    virtual void Release()
        {
        // Override so color does not get reset
        }
   };
