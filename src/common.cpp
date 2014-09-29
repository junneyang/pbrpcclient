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
#include "common.h"

using namespace std;

inline google::protobuf::Message* createMessage(const string& type_name) {
	google::protobuf::Message* message = NULL;
	const google::protobuf::Descriptor* descriptor = google::protobuf::DescriptorPool::generated_pool()->FindMessageTypeByName(type_name);
	if (descriptor) {
		const google::protobuf::Message* prototype = google::protobuf::MessageFactory::generated_factory()->GetPrototype(descriptor);
		if (prototype) {
			message = prototype->New();
		}
	}
	return message;
}

const google::protobuf::MethodDescriptor* FindMethodByName(const string& service_name, const string& method_name) {
	const google::protobuf::ServiceDescriptor* descriptor =
		google::protobuf::DescriptorPool::generated_pool()->FindServiceByName(service_name);
	if (NULL == descriptor) {
		cout << "method not fund ERROR : " << endl;
		return NULL;
	}
	return descriptor->FindMethodByName(method_name);
}

google::protobuf::Message* GetMessageByMethodDescriptor(const google::protobuf::MethodDescriptor* descripter, bool is_input) {
	if (NULL == descripter) {
		cout << "descripter null ERROR : " << endl;
		return NULL;
	}
	const google::protobuf::Descriptor* message_descriptor = NULL;
	if (is_input) {
		message_descriptor = descripter->input_type();
	} else {
		message_descriptor = descripter->output_type();
	}
	const google::protobuf::Message* prototype = google::protobuf::MessageFactory::generated_factory()->GetPrototype(message_descriptor);
	if (NULL == prototype) {
		cout << "get prototype null ERROR : " << endl;
		return NULL;
	}
	google::protobuf::Message* message = prototype->New();
	return message;
}

google::protobuf::Message* GetMessageByName(const string& service_name, const string& method_name, bool is_input) {
	const google::protobuf::MethodDescriptor* descripter = FindMethodByName(service_name, method_name);
	return GetMessageByMethodDescriptor(descripter, is_input);
}

void callback (google::protobuf::Message* request_msg, google::protobuf::Message* response_msg, google::protobuf::RpcController* cntl, int *params) {
	string json_string;
	string error;
	if(ProtoMessageToJson(*response_msg, &json_string, &error)) {
		cout << json_string << endl;
	} else {
		cout << "ProtoMessageToJson ERROR : " << error << endl;
	}
	*params = 1;
	
	delete request_msg;
	delete response_msg;
	delete cntl;
}

///////////////////////////////////////////////////////////////////////////////
string getfilestr(string filepath) {
	ifstream file(filepath.c_str());
	ostringstream filestr;
	char temp;
	if (file.is_open() == true) {
		while (file.peek() != EOF) {
			file.get(temp);	// read the data one character by another
			filestr << temp;
		}
	}
	file.close();
	return filestr.str();
}

std::vector<std::string> split_string(const std::string& str, const std::string& sep){
	std::vector<std::string> ret;
	size_t start = 0;
	size_t str_len = str.size();
	size_t found = std::string::npos;
	while (start < str_len && (found = str.find(sep, start)) != std::string::npos)
	{
		if (found > start)
		{
			std::string sub = str.substr(start, found - start);
			if (!sub.empty())
			{
				ret.push_back(sub);
			}
		}
		start = (found + sep.size());
	}
	if (start < str_len)
	{
		std::string sub = str.substr(start);
		if (!sub.empty())
		{
			ret.push_back(sub);
		}
	}
	return ret;
}

std::string exec_cmd(const char* cmd) {
	FILE* pipe = popen(cmd, "r");
	if (!pipe) return "ERROR";
	char buffer[128];
	std::string result = "";
	while(!feof(pipe)) {
		if(fgets(buffer, 128, pipe) != NULL)
			result += buffer;
	}
	pclose(pipe);
	return result;
}

void helpinfo() {
	cout << "======================================================================================\n";
	cout << "|                                 Usage Instructions                                 |\n";
	cout << "======================================================================================\n";
	cout << "|USAGE          : ./pbrpcclient <PBTYPE> <IPPORT> <ServiceName> <MethodName> <TEST_DATA>\n";
	cout << "|       PBTYPE  : type of pbrpc, currently supported PUBLIC-PBRPC/SOFA-PBRPC/HULU-PBRPC, eg : SOFA-PBRPC \n";
	cout << "|       IPPORT  : sever ip port pair, eg : 127.0.0.1:7789 \n";
	cout << "|  ServiceName  : service name, eg : lbs.da.openservice.UserService \n";
	cout << "|   MethodName  : method name, eg : GetNuomiUserPreference \n";
	cout << "|    TEST_DATA  : test data file path, eg : ./data/nuomi_up.data \n|\n";
	cout << "|EXAMPLE        : ./pbrpcclient SOFA-PBRPC 127.0.0.1:7789 lbs.da.openservice.UserService GetNuomiUserPreference ./data/nuomi_up.data \n";
	cout << "|-------------------------------------------------------------------------------------\n";
	cout << "|MORE           : if any questions, please contact 597092663@qq.com \n";
	cout << "======================================================================================\n";
}

