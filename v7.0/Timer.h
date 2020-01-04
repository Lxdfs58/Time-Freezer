#ifndef _TIMER_H_
#define _TIMER_H_
 
class Timer
{
private:
    unsigned timeout;
    unsigned timepass;
 
public:
    Timer(unsigned timeout = 0) :
        timeout(timeout), timepass(0)
    {
    }
 
public:
    void Reset()
    {
        if( timeout && timeout <= timepass )
            timepass -= timeout;
        else
            timepass = 0;
    }
 
    void Reset(unsigned timeout)
    {
        Reset();
 
        if( timeout )
            this->timeout = timeout;
    }
 
    void Update(unsigned timepass)
    {
        this->timepass += timepass;
    }
 
    bool IsExpired() const
    {
        return timepass >= timeout;
    }
};
#endif
