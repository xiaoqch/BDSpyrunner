// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class PlayerScoreboardEventListener {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_PLAYERSCOREBOARDEVENTLISTENER
public:
    class PlayerScoreboardEventListener& operator=(class PlayerScoreboardEventListener const&) = delete;
    PlayerScoreboardEventListener(class PlayerScoreboardEventListener const&) = delete;
    PlayerScoreboardEventListener() = delete;
#endif

public:
    /*0*/ virtual ~PlayerScoreboardEventListener();
    /*1*/ virtual int /*enum enum EventResult*/ onScoreChanged(struct ScoreboardId const&, std::string const&, int);
    /*
    inline  ~PlayerScoreboardEventListener(){
         (PlayerScoreboardEventListener::*rv)();
        *((void**)&rv) = dlsym("??1PlayerScoreboardEventListener@@UEAA@XZ");
        return (this->*rv)();
    }
    */
    MCAPI class SubscribedObjectives& getPlayerSubscriptions(struct ScoreboardId const&, class Player const&);
    MCAPI void removePlayerSubscriptions(struct ScoreboardId const&);

protected:

private:

};