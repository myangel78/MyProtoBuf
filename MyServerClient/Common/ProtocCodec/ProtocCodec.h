#pragma once

#include "ProtocCodec_global.h"

#include <google/protobuf/descriptor.h>
#include <google/protobuf/message.h>
#include <zlib.h>  // adler32

#include <string>

//#include <arpa/inet.h>  // htonl, ntohl
#include <winsock2.h>
#include <Windows.h>
#include <stdint.h>


class PROTOCCODEC_EXPORT ProtocCodec
{
public:
    ProtocCodec();
public:
    std::string encode(const google::protobuf::Message &message);
    google::protobuf::Message *createMessage(const std::string &type_name);
    google::protobuf::Message *decode(const std::string &buf);
    int32_t asInt32(const char *buf);
};
