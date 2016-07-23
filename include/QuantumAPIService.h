/*
 * QuantumAPIService.h
 *
 *  Created on: Jun 17, 2016
 *      Author: guille
 */

#ifndef INCLUDE_QUANTUMAPISERVICE_H_
#define INCLUDE_QUANTUMAPISERVICE_H_

#include <curl/curl.h>

using std::string;
using std::ifstream;

namespace qi 
{

class QuantumAPIService {

private:

	string fileName;

	string json;
	string jsonExperimentName; //JSON file with the name of the experiment used for get the code ID
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

} // namespace qi

#endif /* INCLUDE_QUANTUMAPISERVICE_H_ */

