/*
 * QuantumAPIService.h
 *
 *  Created on: Jun 17, 2016
 *      Author: guille
 */

#ifndef INCLUDE_QUANTUMAPISERVICE_H_
#define INCLUDE_QUANTUMAPISERVICE_H_

#include <fstream>
#include <sstream>
#include <iostream>
#include <curl/curl.h>

using namespace std;

class QuantumAPIService {

private:

	string json;
	/*JSON file with the name of the experiment used for get the code ID*/
	string jsonExperimentName;
	ifstream inputFlow;
	CURL *curl;

	string doPost(const char* url, const char* postFields, const char* token);
	void getAccessTokenAndUserID(string &userID, string &accessToken);
	string getCodeID(string userID, string accessToken);
	string query(string userID, string accessToken, string codeID);

	void jsonExperimentNameParse();

public:
	QuantumAPIService(string inputName);

	void sendJsonFileToTheAPI();

	virtual ~QuantumAPIService();
};

#endif /* INCLUDE_QUANTUMAPISERVICE_H_ */

