/*
 * QuantumAPIService.cpp
 *
 *  Created on: Jun 17, 2016
 *      Author: guille
 */

#include "QuantumAPIService.h"

QuantumAPIService::QuantumAPIService(string inputName) {

	inputFlow.open(inputName);
	getline(inputFlow,json);
	jsonExperimentNameParse();
	curl = curl_easy_init();
}

size_t writeFunction(void *ptr, size_t size, size_t nmemb, std::string* data) {
	data->append((char*) ptr, size * nmemb);
	return size * nmemb;
}

string QuantumAPIService::doPost(const char* url, const char* postFields, const char* token = NULL){
	std::string response_string;
	curl_easy_setopt(curl, CURLOPT_URL, url);
	struct curl_slist *chunk = NULL;
	if(token!=NULL){
		chunk = curl_slist_append(chunk, token);
		chunk = curl_slist_append(chunk, "Content-Type: application/json");
		curl_easy_setopt(curl, CURLOPT_HTTPHEADER, chunk);
	}
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeFunction);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response_string);
	curl_easy_setopt(curl, CURLOPT_POSTFIELDS, postFields);
	curl_easy_perform(curl);
	return response_string;
}

void QuantumAPIService::getAccessTokenAndUserID(string &userID, string &accessToken) {
	string response_string=doPost("https://quantumexperience.ng.bluemix.net/api/users/login?include=user", "email=qinterpreter12@gmail.com&password=quantumfoo12");
	accessToken = response_string.substr(7,64);
	userID = response_string.substr(134,32);
}

void QuantumAPIService::sendJsonFileToTheAPI() {

	string a,b,c;

	getAccessTokenAndUserID(a,b);

	c = getCodeID(a,b);

	cout << a << " " << b << " " << c << endl;

	string responseJSON = query(a,b,c);

	ofstream outputFlow;
	outputFlow.open("../examples/response.json");
	outputFlow << responseJSON;
	outputFlow.close();
}

string QuantumAPIService::getCodeID(string userID, string accessToken){
	stringstream urlReq;
	urlReq << "https://quantumexperience.ng.bluemix.net/api/users/" << userID << "/codes";
	stringstream token;
	token << "X-Access-Token: " << accessToken;
	std::string response_string = doPost(urlReq.str().c_str(), jsonExperimentName.c_str(), token.str().c_str());
	string codeID = response_string.substr(58,32);
	return codeID;
}

string QuantumAPIService::query(string userID, string accessToken, string codeID){
	stringstream urlReq;
	urlReq << "https://quantumexperience.ng.bluemix.net/api/users/" << userID  << "/codes/" << codeID << "/executions?deviceRunType=sim_trivial&fromCache=true";
	stringstream token;
	token << "X-Access-Token: " << accessToken;
	std::string response_string = doPost(urlReq.str().c_str(), json.c_str(), token.str().c_str());
	return response_string;
}

void QuantumAPIService::jsonExperimentNameParse() {

	string temp;
	temp = json.substr (12);
	jsonExperimentName = "{\"name\":\"autoExperiment\",\"jsonQASM\":" + temp;
}

QuantumAPIService::~QuantumAPIService() {

	inputFlow.close();
	curl_easy_cleanup(curl);
	curl = NULL;
}


