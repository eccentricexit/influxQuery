/*
 ============================================================================
 Name        : influxQuery.c
 Author      : Matheus Faria
 Version     :
 Copyright   : GNU GPL
 Description : Posting HTTP to influxDB
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <curl/curl.h>

int main(void) {

	//insert query example
	char insert[100] =
			"cpu_load_short,host=server01,region=us-east value=0.234 1434055162000000000";

	//select example
	//char select[100] = "SELECT value FROM cpu_load_short WHERE region='us-west'";

	CURL *curl;
	CURLcode res;

	curl = curl_easy_init();
	if (curl) {

		curl_easy_setopt(curl, CURLOPT_URL,
				"http://localhost:8086/write?db=mydb");
		/* POST data */
		curl_easy_setopt(curl, CURLOPT_POSTFIELDS, insert);

		/* Perform the request, res will get the return code */
		res = curl_easy_perform(curl);
		/* Check for errors */
		if (res != CURLE_OK)
			fprintf(stderr, "curl_easy_perform() failed: %s\n",
					curl_easy_strerror(res));

		curl_easy_cleanup(curl);
	}
	curl_global_cleanup();

	curl_easy_init();
	return EXIT_SUCCESS;
}

