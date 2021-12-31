// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "Packet.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class TakeItemActorPacket : public Packet {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_TAKEITEMACTORPACKET
public:
    class TakeItemActorPacket& operator=(class TakeItemActorPacket const&) = delete;
    TakeItemActorPacket(class TakeItemActorPacket const&) = delete;
#endif

public:
    /*0*/ virtual ~TakeItemActorPacket();
    /*1*/ virtual enum MinecraftPacketIds getId() const;
    /*2*/ virtual std::string getName() const;
    /*3*/ virtual void write(class BinaryStream&) const;
    /*4*/ virtual bool disallowBatching() const;
    /*5*/ virtual enum StreamReadResult _read(class ReadOnlyBinaryStream&);
    /*
    inline  ~TakeItemActorPacket(){
         (TakeItemActorPacket::*rv)();
        *((void**)&rv) = dlsym("??1TakeItemActorPacket@@UEAA@XZ");
        return (this->*rv)();
    }
    */
    MCAPI TakeItemActorPacket(class ActorRuntimeID, class ActorRuntimeID);
    MCAPI TakeItemActorPacket();

protected:

private:

};