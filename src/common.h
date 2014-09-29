 /*
 *Copyright (c) 2014-2014, yangjun <597092663@qq.com>
 *All rights reserved.
 * 
 *Redistribution and use in source and binary forms, with or without
 *modification, are permitted provided that the following conditions are met:
 * 
 *  * Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *  * Neither the name of Redis nor the names of its contributors may be used
 *    to endorse or promote products derived from this software without
 *    specific prior written permission.
 * 
 *THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
 *AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 *IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 *ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS 
 *BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 *CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
 *SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
 *INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
 *CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 *ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF 
 *THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef COMMON__H_
#define COMMON__H_
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>
#include <cstring>
#include <vector>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <algorithm>
#include <pthread.h>
#include <unistd.h>

#include "user_proto.h"

#include <google/protobuf/message.h>
#include <google/protobuf/descriptor.h>

#include "pb_to_json.h"
#include "json_to_pb.h"

//SOFA-PBRPC
#include "sofa/pbrpc/rpc_channel.h"
#include "sofa/pbrpc/common.h"
#include "sofa/pbrpc/rpc_controller.h"
#include "sofa/pbrpc/pbrpc.h"

//PUBLIC-PBRPC
#include <ub_log.h>
#include <ubclient_include.h>
#include "ubclient_manager2.h"
#include <comlogplugin.h>
#include "BlockingClient.h"
#include "NonblockingClient.h"
#include "AsyncClient.h"
#include "UbTransport.h"
#include "PbProtocol.h"
#include <Configure.h>
#include "util/pbrpc_log.h"

//HULU-PBRPC
#include "hulu/pbrpc/rpc_channel.h"
#include "hulu/pbrpc/sync_point.h"
#include "hulu/pbrpc/common.h"
#include "hulu/pbrpc/rpc_client_controller.h"

using namespace std;

inline google::protobuf::Message* createMessage(const string& type_name);
const google::protobuf::MethodDescriptor* FindMethodByName(const string& service_name, const string& method_name);
google::protobuf::Message* GetMessageByMethodDescriptor(const google::protobuf::MethodDescriptor* descripter, bool is_input);
google::protobuf::Message* GetMessageByName(const string& service_name, const string& method_name, bool is_input);
void callback (google::protobuf::Message* request_msg, google::protobuf::Message* response_msg, google::protobuf::RpcController* cntl, int *params);

string getfilestr(string filepath);
std::vector<std::string> split_string(const std::string& str, const std::string& sep);
std::string exec_cmd(const char* cmd);
void helpinfo();
#endif /* COMMON__H_ */

