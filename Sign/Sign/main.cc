
#include <stdio.h>
#include <iostream>
#include <stdint.h>
#include <string>
#include <map>
#include <openssl/hmac.h>
#include <algorithm>
#include <cctype>

using namespace std;

#pragma comment(lib,"libeay32.lib")
#pragma comment(lib,"ssleay32.lib")


string GetStrAKSK(map<string, string> dicData, string key);

void  GetSign(map<string, string> data, string strkey, string & strRest);

int main()
{
	map<string, string> data;
	string strData;
	string strkey = "sdfsdfs";
	data["app_id"] = "120001";

	GetSign(data, strkey, strData);
	cout << strData << endl;
	getchar();
}

string GetStrAKSK(map<string,string> dicData,string key)
{
	string strData = "";
	map<string, string>::iterator iter;
	iter = dicData.begin();
	while (iter != dicData.end())
	{
		if (strData.empty())
		{
			strData = iter->first + "=" + iter->second;
		}
		else
		{
			strData +="&"+ iter->first + "=" + iter->second;
		}
		iter++;
	}
	strData += "&key="+key;

	return strData;

}

void GetSign(map<string, string> data, string strkey, string & strRest)
{
	string strData = GetStrAKSK(data, strkey);
	unsigned char* result;
	unsigned int len = 32;
	result = (unsigned char*)malloc(sizeof(char) * strData.length());
	HMAC_CTX ctx;
	HMAC_CTX_init(&ctx);
	// Using sha1 hash engine here.
	// You may use other hash engines. e.g EVP_md5(), EVP_sha224, EVP_sha512, etc
	HMAC_Init_ex(&ctx, strkey.c_str(), strkey.length(), EVP_sha256(), NULL);
	HMAC_Update(&ctx, (unsigned char*)strData.c_str(), strData.length());
	HMAC_Final(&ctx, result, &len);
	HMAC_CTX_cleanup(&ctx);

	char buf[33] = { '\0' };
	char tmp[3] = { '\0' };
	int i;

	for (i = 0; i < 32; i++){
		sprintf(tmp, "%2.2x", result[i]);
		strRest.append(tmp);
	}
	std::transform(strRest.begin(), strRest.end(), strRest.begin(), std::toupper);
}
