
#include "DeviceCtl.h"


int DeviceCtl::connect(int port) {
	dllHandle = LoadLibrary(L"termb.dll");
	if (dllHandle != NULL)
	{
		CVR_InitComm = (lpCVR_InitComm)GetProcAddress(dllHandle, "CVR_InitComm");
		CVR_CloseComm = (lpCVR_CloseComm)GetProcAddress(dllHandle, "CVR_CloseComm");
		CVR_Authenticate = (lpCVR_Authenticate)GetProcAddress(dllHandle, "CVR_Authenticate");
		CVR_AuthenticateForNoJudge = (lpCVR_AuthenticateForNoJudge)GetProcAddress(dllHandle, "CVR_AuthenticateForNoJudge");
		CVR_Read_Content = (lpCVR_Read_Content)GetProcAddress(dllHandle, "CVR_Read_FPContent");
		CVR_GetNationCode = (lpGetNationCode)GetProcAddress(dllHandle, "GetNationCode");
		CVR_SetComBaudrate = (lpCVR_SetBaudRate)GetProcAddress(dllHandle, "CVR_SetBaudRate");

		/*	M1_MF_HL_Request        = (lpM1_MF_HL_Request)GetProcAddress(dllHandle,"M1_MF_HL_Request");
			M1_MF_HL_Auth			= (lpM1_MF_HL_Auth)GetProcAddress(dllHandle,"M1_MF_HL_Auth");
			M1_MF_HL_Read			= (lpM1_MF_HL_Read)GetProcAddress(dllHandle,"M1_MF_HL_Read");
			M1_MF_HL_Write			= (lpM1_MF_HL_Write)GetProcAddress(dllHandle,"M1_MF_HL_Write");*/

#ifdef UNICODE
		CVR_GetPeopleName = (lpGetPeopleName)GetProcAddress(dllHandle, "GetPeopleNameU");
		CVR_GetPeopleSex = (lpGetPeopleSex)GetProcAddress(dllHandle, "GetPeopleSexU");
		CVR_GetPeopleNation = (lpGetPeopleNation)GetProcAddress(dllHandle, "GetPeopleNationU");
		CVR_GetPeopleBirthday = (lpGetPeopleBirthday)GetProcAddress(dllHandle, "GetPeopleBirthdayU");
		CVR_GetPeopleAddress = (lpGetPeopleAddress)GetProcAddress(dllHandle, "GetPeopleAddressU");
		CVR_GetPeopleIDCode = (lpGetPeopleIDCode)GetProcAddress(dllHandle, "GetPeopleIDCodeU");
		CVR_GetDepartment = (lpGetDepartment)GetProcAddress(dllHandle, "GetDepartmentU");
		CVR_GetStartDate = (lpGetStartDate)GetProcAddress(dllHandle, "GetStartDateU");
		CVR_GetEndDate = (lpGetEndDate)GetProcAddress(dllHandle, "GetEndDateU");
		CVR_GetSAMID = (lpCVR_GetSAMIDU)GetProcAddress(dllHandle, "CVR_GetSAMIDU");
		CVR_GetPeopleChineseName = (lpGetPeopleChineseName)GetProcAddress(dllHandle, "GetPeopleChineseNameU");
		CVR_GetPeopleCertVersion = (lpGetPeopleCertVersion)GetProcAddress(dllHandle, "GetPeopleCertVersionU");
		CVR_GetNationCodeStrU = (lpGetNationCodeStrU)GetProcAddress(dllHandle, "GetNationCodeU");
		CVR_GetIDCardUID = (lpCVR_GetIDCardUID)GetProcAddress(dllHandle, "CVR_GetIDCardUIDU");
		CVR_lpGetPassCheckID = (lpGetPassCheckID)GetProcAddress(dllHandle, "GetPassCheckIDU");
		CVR_lpGetIssuesNum = (lpGetIssuesNum)GetProcAddress(dllHandle, "GetIssuesNumU");
		CVR_lpGetCertType = (lpGetCertType)GetProcAddress(dllHandle, "GetCertTypeU");
		CVR_Getbase64BMPData = (lpGetbase64BMPData)GetProcAddress(dllHandle, "Getbase64BMPDataU");
		CVR_Getbase64JpgData = (lpGetbase64JpgData)GetProcAddress(dllHandle, "Getbase64JpgDataU");
		CVR_GetBMPData = (lpGetBMPData)GetProcAddress(dllHandle, "GetBMPDataU");
		CVR_GetJpgData = (lpGetJpgData)GetProcAddress(dllHandle, "GetJpgDataU");


#else
		CVR_GetPeopleName = (lpGetPeopleName)GetProcAddress(dllHandle, "GetPeopleName");
		CVR_GetPeopleSex = (lpGetPeopleSex)GetProcAddress(dllHandle, "GetPeopleSex");
		CVR_GetPeopleNation = (lpGetPeopleNation)GetProcAddress(dllHandle, "GetPeopleNation");
		CVR_GetPeopleBirthday = (lpGetPeopleBirthday)GetProcAddress(dllHandle, "GetPeopleBirthday");
		CVR_GetPeopleAddress = (lpGetPeopleAddress)GetProcAddress(dllHandle, "GetPeopleAddress");
		CVR_GetPeopleIDCode = (lpGetPeopleIDCode)GetProcAddress(dllHandle, "GetPeopleIDCode");
		CVR_GetDepartment = (lpGetDepartment)GetProcAddress(dllHandle, "GetDepartment");
		CVR_GetStartDate = (lpGetStartDate)GetProcAddress(dllHandle, "GetStartDate");
		CVR_GetEndDate = (lpGetEndDate)GetProcAddress(dllHandle, "GetEndDate");
		CVR_GetPeopleChineseName = (lpCVR_GetSAMIDU)GetProcAddress(dllHandle, "GetPeopleChineseName");
		CVR_GetPeopleCertVersion = (lpCVR_GetSAMIDU)GetProcAddress(dllHandle, "GetPeopleCertVersion");
		CVR_GetIDCardUID = (lpCVR_GetIDCardUID)GetProcAddress(dllHandle, "CVR_GetIDCardUID");
		CVR_lpGetPassCheckID = (lpGetPassCheckID)GetProcAddress(dllHandle, "GetPassCheckID");
		CVR_lpGetIssuesNum = (lpGetIssuesNum)GetProcAddress(dllHandle, "GetIssuesNum");
		CVR_Getbase64BMPData = (lpGetbase64BMPData)GetProcAddress(dllHandle, "Getbase64BMPData");
		CVR_Getbase64JpgData = (lpGetbase64JpgData)GetProcAddress(dllHandle, "Getbase64JpgData");
		CVR_GetBMPData = (lpGetBMPData)GetProcAddress(dllHandle, "GetBMPData");
		CVR_GetJpgData = (lpGetJpgData)GetProcAddress(dllHandle, "GetJpgData");
#endif
	}
	int connect = 0;
	if (port != 0) {
		connect = CVR_InitComm(port);
	}
	else {
		for (int i = 1001; i <= 1016; i++)
		{
			if (CVR_InitComm(i) == 1)
			{
				connect = 1;
				port = i;
				break;
			}
		}
	}

	if (connect == 0) {
		isConnect = false;
		std::cout << "无法连接设备\n";
		return 0;
	}
	isConnect = true;
	std::cout << "设备已连接\n";
	return 1;
}


char* TCHARToChar(TCHAR* pTchar)
{
	char* pChar = nullptr;
	int nLen = wcslen(pTchar) + 1;
	pChar = new char[nLen * 2];
	WideCharToMultiByte(CP_ACP, 0, pTchar, nLen, pChar, 2 * nLen, NULL, NULL);
	return pChar;
}

void DeviceCtl::loadIdCard(IdCard* idcard) {
	int nLen;
	TCHAR szContent[MAX_PATH];
	nLen = sizeof(szContent);
	if (CVR_GetPeopleName)//姓名
	{
		memset(szContent, 0, sizeof(szContent));
		CVR_GetPeopleName((BYTE*)szContent, &nLen);
		idcard->name = TCHARToChar(szContent);
	}

	if (CVR_GetPeopleSex)//性别
	{
		memset(szContent, 0, sizeof(szContent));
		CVR_GetPeopleSex((BYTE*)szContent, &nLen);
		idcard->sex = TCHARToChar(szContent);
	}

	if (CVR_GetPeopleNation)//民族
	{
		memset(szContent, 0, sizeof(szContent));
		CVR_GetPeopleNation((BYTE*)szContent, &nLen);
		idcard->nation = TCHARToChar(szContent);
	}

	if (CVR_GetPeopleBirthday)//出生日期
	{
		memset(szContent, 0, sizeof(szContent));
		CVR_GetPeopleBirthday((BYTE*)szContent, &nLen);
		idcard->birthday = TCHARToChar(szContent);
	}

	if (CVR_GetPeopleAddress)//地址
	{
		memset(szContent, 0, sizeof(szContent));
		CVR_GetPeopleAddress((BYTE*)szContent, &nLen);
		idcard->address = TCHARToChar(szContent);
	}

	if (CVR_GetPeopleIDCode)//证件号码
	{
		memset(szContent, 0, sizeof(szContent));
		CVR_GetPeopleIDCode((BYTE*)szContent, &nLen);
		idcard->idCode = TCHARToChar(szContent);
	}

	if (CVR_GetDepartment)//签发机关
	{
		memset(szContent, 0, sizeof(szContent));
		CVR_GetDepartment((BYTE*)szContent, &nLen);
		idcard->civicDepartment = TCHARToChar(szContent);
	}

	/*
	* 不知道为什么获取不到...
	if (CVR_Getbase64BMPData)//头像图片
	{
		unsigned char x[38862 * 2];
		memset(x, 0, sizeof(x));
		nLen = sizeof(x);
		CVR_Getbase64BMPData((BYTE*)x, &nLen);
		cout << x;
		idcard->base64Bmp = TCHARToChar(szContent);
	}
	*/
	
}

int DeviceCtl::authenticate() {
	return CVR_Authenticate();
}

string DeviceCtl::read(IdCard* idcard) {
	if (CVR_Read_Content() != 1) {
		return "err";
	}
	loadIdCard(idcard);
	return idcard->name + "|" +
		idcard->idCode + "|" +
		idcard->sex + "|" +
		idcard->birthday + "|" +
		idcard->nation + "|" +
		idcard->address + "|" +
		idcard->civicDepartment + "|" +
		idcard->base64Bmp;
}

int DeviceCtl::close() {
	int close;
	close = CVR_CloseComm();
	if (close == 1) {
		isConnect = true;
		std::cout << "已断开设备连接\n";
		return 1;
	}
	else {
		std::cout << "发生异常_"<<close<<"\n";
		return 0;
	}
};