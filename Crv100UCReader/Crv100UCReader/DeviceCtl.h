#pragma once

#include "IdCard.h"
#include <iostream>
#include <string>
#include "Windows.h"
#include "DeviceCtl.h"
#include "Crv100UCReader.h"
#include <WTypesbase.h>

using namespace std;


typedef int(PASCAL* lpCVR_InitComm)(int port);
typedef int(PASCAL* lpCVR_CloseComm)();
typedef int(PASCAL* lpCVR_Authenticate)();
typedef int(PASCAL* lpCVR_AuthenticateForNoJudge)();
typedef int(PASCAL* lpCVR_Read_Content)();
typedef int(PASCAL* lpCVR_SetBaudRate)(int nBaudRate);

typedef int(PASCAL* lpGetPeopleName)(unsigned char* strTmp, int* strLen);
typedef int(PASCAL* lpGetPeopleSex)(unsigned char* strTmp, int* strLen);
typedef int(PASCAL* lpGetPeopleNation)(unsigned char* strTmp, int* strLen);
typedef int(PASCAL* lpGetPeopleBirthday)(unsigned char* strTmp, int* strLen);
typedef int(PASCAL* lpGetPeopleAddress)(unsigned char* strTmp, int* strLen);
typedef int(PASCAL* lpGetPeopleIDCode)(unsigned char* strTmp, int* strLen);
typedef int(PASCAL* lpGetDepartment)(unsigned char* strTmp, int* strLen);
typedef int(PASCAL* lpGetStartDate)(unsigned char* strTmp, int* strLen);
typedef int(PASCAL* lpGetEndDate)(unsigned char* strTmp, int* strLen);
typedef int(PASCAL* lpGetNationCode)(UCHAR* sexData, int* pLen);
typedef int(PASCAL* lpGetNationCodeStrU)(unsigned char* nationData, int* pLen);
typedef int(PASCAL* lpCVR_GetSAMIDU)(unsigned char* SAMID);

typedef int(PASCAL* lpCVR_GetIDCardUID)(char* pUidBuff, int nBuffLen);

typedef int(PASCAL* lpGetPeopleChineseName)(unsigned char* strTmp, int* strLen);
typedef int(PASCAL* lpGetPeopleCertVersion)(unsigned char* strTmp, int* strLen);

typedef int (PASCAL* lpGetbase64BMPData)(unsigned char* pData, int* pLen);
typedef int (PASCAL* lpGetbase64JpgData)(unsigned char* pData, int* pLen);
typedef int (PASCAL* lpGetBMPData)(unsigned char* pData, int* pLen);
typedef int (PASCAL* lpGetJpgData)(unsigned char* pData, int* pLen);

// 港澳通行证
typedef int (PASCAL* lpGetPassCheckID)(unsigned char* strTmp, int* strLen);
typedef int (PASCAL* lpGetIssuesNum)(int* IssuesNum);
typedef int (PASCAL* lpGetCertType)(unsigned char* strTmp, int* strLen);

class DeviceCtl {
public:
	bool isConnect;

	HINSTANCE dllHandle;

	lpCVR_InitComm CVR_InitComm;
	lpCVR_CloseComm CVR_CloseComm;
	lpCVR_Authenticate CVR_Authenticate;
	lpCVR_AuthenticateForNoJudge CVR_AuthenticateForNoJudge;
	lpCVR_Read_Content CVR_Read_Content;
	lpCVR_GetSAMIDU CVR_GetSAMID;
	lpCVR_SetBaudRate CVR_SetComBaudrate;

	lpGetPeopleChineseName CVR_GetPeopleChineseName;
	lpGetPeopleCertVersion CVR_GetPeopleCertVersion;

	lpGetPeopleName CVR_GetPeopleName;
	lpGetPeopleSex CVR_GetPeopleSex;
	lpGetPeopleNation CVR_GetPeopleNation;
	lpGetPeopleBirthday CVR_GetPeopleBirthday;
	lpGetPeopleAddress CVR_GetPeopleAddress;
	lpGetPeopleIDCode CVR_GetPeopleIDCode;
	lpGetDepartment CVR_GetDepartment;
	lpGetStartDate CVR_GetStartDate;
	lpGetEndDate CVR_GetEndDate;
	lpGetNationCode CVR_GetNationCode;
	lpGetNationCodeStrU CVR_GetNationCodeStrU;
	lpCVR_GetIDCardUID CVR_GetIDCardUID;
	lpGetbase64BMPData CVR_Getbase64BMPData;
	lpGetbase64JpgData CVR_Getbase64JpgData;
	lpGetBMPData CVR_GetBMPData;
	lpGetJpgData CVR_GetJpgData;

	//港澳台
	lpGetPassCheckID CVR_lpGetPassCheckID;
	lpGetIssuesNum CVR_lpGetIssuesNum;
	lpGetCertType CVR_lpGetCertType;

	int connect(int port);
	int authenticate();
	string read(IdCard* idcard);
	int close();
	
protected:
	void loadIdCard(IdCard* idcard);

};