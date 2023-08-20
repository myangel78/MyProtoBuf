#!/bin/bash

PROTO_LOCATION=./protobuf/protoc
SRC_DIR=./
DST_DIR=./
SRC_DIR=./
PROTO_NAME=query.proto
 
$PROTO_LOCATION -I=$SRC_DIR --cpp_out=$DST_DIR $SRC_DIR/$PROTO_NAME

#./protobuf/protoc.exe -I=./ --cpp_out=./ ./query.proto
 