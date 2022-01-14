// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "Json.hpp"
#include "Packet.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class ScriptCustomEventPacket : public Packet {

#define AFTER_EXTRA
// Add Member There

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_SCRIPTCUSTOMEVENTPACKET
public:
    class ScriptCustomEventPacket& operator=(class ScriptCustomEventPacket const&) = delete;
    ScriptCustomEventPacket(class ScriptCustomEventPacket const&) = delete;
#endif

public:
    /*0*/ virtual ~ScriptCustomEventPacket();
    /*1*/ virtual enum MinecraftPacketIds getId() const;
    /*2*/ virtual std::string getName() const;
    /*3*/ virtual void write(class BinaryStream&) const;
    /*4*/ virtual bool disallowBatching() const;
    /*5*/ virtual enum StreamReadResult _read(class ReadOnlyBinaryStream&);
    /*
    inline  ~ScriptCustomEventPacket(){
         (ScriptCustomEventPacket::*rv)();
        *((void**)&rv) = dlsym("??1ScriptCustomEventPacket@@UEAA@XZ");
        return (this->*rv)();
    }
    */
    MCAPI ScriptCustomEventPacket(std::string const&, class Json::Value const&);
    MCAPI ScriptCustomEventPacket();
    MCAPI class Json::Value const& getData() const;
    MCAPI std::string const& getEventName() const;

protected:

private:

};