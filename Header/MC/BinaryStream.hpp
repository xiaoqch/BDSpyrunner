// This Header is auto generated by BDSLiteLoader Toolchain
#pragma once
#define AUTO_GENERATED
#include "../Global.h"
#include "ReadOnlyBinaryStream.hpp"

#define BEFORE_EXTRA
// Include Headers or Declare Types Here

#undef BEFORE_EXTRA

class BinaryStream : public ReadOnlyBinaryStream {

#define AFTER_EXTRA
// Add Member There
public:
    std::string writeBuf, *pwBuf;

    LIAPI void reserve(size_t size);
    LIAPI std::string& getRaw();

#undef AFTER_EXTRA

#ifndef DISABLE_CONSTRUCTOR_PREVENTION_BINARYSTREAM
public:
    class BinaryStream& operator=(class BinaryStream const&) = delete;
    BinaryStream(class BinaryStream const&) = delete;
#endif

public:
    /*0*/ virtual ~BinaryStream();
    /*
    inline  ~BinaryStream(){
         (BinaryStream::*rv)();
        *((void**)&rv) = dlsym("??1BinaryStream@@UEAA@XZ");
        return (this->*rv)();
    }
    */
    MCAPI BinaryStream(std::string&, bool);
    MCAPI BinaryStream();
    MCAPI std::string getAndReleaseData();
    MCAPI void reset();
    MCAPI void writeBool(bool);
    MCAPI void writeByte(unsigned char);
    MCAPI void writeDouble(double);
    MCAPI void writeFloat(float);
    MCAPI void writeSignedBigEndianInt(int);
    MCAPI void writeSignedInt(int);
    MCAPI void writeSignedInt64(__int64);
    MCAPI void writeSignedShort(short);
    MCAPI void writeString(class gsl::basic_string_span<char const, -1>);
    MCAPI void writeUnsignedChar(unsigned char);
    MCAPI void writeUnsignedInt(unsigned int);
    MCAPI void writeUnsignedInt64(unsigned __int64);
    MCAPI void writeUnsignedShort(unsigned short);
    MCAPI void writeUnsignedVarInt(unsigned int);
    MCAPI void writeUnsignedVarInt64(unsigned __int64);
    MCAPI void writeVarInt(int);
    MCAPI void writeVarInt64(__int64);

protected:

private:
    MCAPI void write(void const*, unsigned __int64);

};