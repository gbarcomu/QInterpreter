/*
 * QuantumAPIService.cpp
 *
 *  Created on: Jun 17, 2016
 *      Author: guille
 */
#include <fstream>
#include <sstream>
#include <iostream>

#include "QuantumAPIService.h"

using std::ofstream;
using std::stringstream;
using std::cout;
using std::endl;

//#define CHECK_CURL_ERRORS

namespace qi 
{

QuantumAPIService::QuantumAPIService(string inputName)
{
	fileName = inputName;
	inputFlow.open(inputName.c_str());
	getline(inputFlow,json);
	jsonExperimentNameParse();
	curl = curl_easy_init();
}

size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string* data)
{
	data->append((char*) ptr, size * nmemb);
	return size * nmemb;
}

string QuantumAPIService::doPost(const char* url, const char* postFields, const char* token = NULL)
{
	string response_string;
	curl_easy_setopt(curl, CURLOPT_URL, url);
	struct curl_slist *chunk = NULL;

	if(token!=NULL){
		chunk = curl_slist_append(chunk, token);
		chunk = curl_slist_append(chunk, "Content-Type: application/json");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
	}

#ifdef CHECK_CURL_ERRORS
	char curl_err_buf[512];
	curl_easy_setopt(curl, CURLOPT_ERRORBUFFER, curl_err_buf);		// set error buffer, if curl fails we need to know why
#endif

	curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, false);			// disable SSL sertificate check
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields);
	
	curl_easy_perform(curl);

#ifdef CHECK_CURL_ERRORS
	char *pBuf = curl_err_buf;
	while ( *pBuf )
		cout << *( pBuf++ );
#endif

	return response_string;
}

void QuantumAPIService::getAccessTokenAndUserID(string &userID, string &accessToken)
{
	string response_string=doPost("https://quantumexperience.ng.bluemix.net/api/users/login?include=user", "email=qinterpreter12@gmail.com&password=quantumfoo12");

	if ( 0 < response_string.length() )
	{
		accessToken = response_string.substr(7, 64);
		userID = response_string.substr(134, 32);
	}
}

void QuantumAPIService::sendJsonFileToTheAPI()
{
	string a,b,c;

	getAccessTokenAndUserID(a,b);

	if ( 0 < a.length() && 0 < b.length() )
	{
		c = getCodeID(a,b);
		//cout << a << " " << b << " " << c << endl;
		if ( 0 < c.length() )
		{
			string responseJSON = query(a,b,c);

			fileName = fileName.substr(0, fileName.length() - 5) + "Result.json";

			ofstream outputFlow;
			outputFlow.open(fileName.c_str());
			outputFlow << responseJSON;
			outputFlow.close();

			cout << "Success" << endl;
		}
		else
		{
			cout << "Fail: getCodeID" << endl;
		}
	}
	else
	{
		cout << "Fail: getAccessTokenAndUserID" << endl;
	}
}

string QuantumAPIService::getCodeID(string userID, string accessToken)
{
	stringstream urlReq;
	urlReq << "https://quantumexperience.ng.bluemix.net/api/users/" << userID << "/codes";
	stringstream token;
	token << "X-Access-Token: " << accessToken;
	std::string response_string = doPost(urlReq.str().c_str(), jsonExperimentName.c_str(), token.str().c_str());

	if ( 0 < response_string.length() )
	{
		string codeID = response_string.substr(58,32);
		return codeID;
	}
	cout << "Fail: doPost" << endl;
	return 0;
}

string QuantumAPIService::query(string userID, string accessToken, string codeID)
{
	stringstream urlReq;
	urlReq << "https://quantumexperience.ng.bluemix.net/api/users/" << userID  << "/codes/" << codeID << "/executions?deviceRunType=sim_realistic&fromCache=false";
	stringstream token;
	token << "X-Access-Token: " << accessToken;
	std::string response_string = doPost(urlReq.str().c_str(), json.c_str(), token.str().c_str());
	if ( 0 < response_string.length() )
	{ 
		return response_string;
	}
	cout << "Fail: doPost" << endl;
	return 0;
}

void QuantumAPIService::jsonExperimentNameParse()
{
	string temp;
	temp = json.substr (12);
	jsonExperimentName = "{\"name\":\"autoExperiment\",\"jsonQASM\":" + temp;
}

QuantumAPIService::~QuantumAPIService()
{
	inputFlow.close();
	curl_easy_cleanup(curl);
	curl = NULL;
}

} // namespace qi
