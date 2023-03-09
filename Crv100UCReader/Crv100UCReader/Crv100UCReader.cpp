// Crv100UCReader.cpp : ���ļ����� "main" ����������ִ�н��ڴ˴���ʼ��������
//


#include <iostream>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <thread>
#include <list>
#include <comdef.h>
#include "DeviceCtl.h"

typedef websocketpp::server<websocketpp::config::asio> WebsocketServer;
typedef WebsocketServer::message_ptr message_ptr;

using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;
using websocketpp::lib::bind;

using namespace std;

WebsocketServer server;
IdCard* idcard = new IdCard();
DeviceCtl* deviceCtl = new DeviceCtl();
list<WebsocketServer::connection_ptr> conns = {};
WebsocketServer::connection_ptr curCon = NULL;

websocketpp::close::status::value cvValue = 0;
std::string strReason = "";

std::string string_To_UTF8(const std::string& str)
{
	int nwLen = ::MultiByteToWideChar(CP_ACP, 0, str.c_str(), -1, NULL, 0);
	wchar_t* pwBuf = new wchar_t[nwLen + 1];//һ��Ҫ��1����Ȼ�����β�� 
	ZeroMemory(pwBuf, nwLen * 2 + 2);
	::MultiByteToWideChar(CP_ACP, 0, str.c_str(), str.length(), pwBuf, nwLen);
	int nLen = ::WideCharToMultiByte(CP_UTF8, 0, pwBuf, -1, NULL, NULL, NULL, NULL);
	char* pBuf = new char[nLen + 1];
	ZeroMemory(pBuf, nLen + 1);
	::WideCharToMultiByte(CP_UTF8, 0, pwBuf, nwLen, pBuf, nLen, NULL, NULL);
	std::string retStr(pBuf);
	delete[]pwBuf;
	delete[]pBuf;
	pwBuf = NULL;
	pBuf = NULL;
	return retStr;
}

void OnOpen(WebsocketServer* server, websocketpp::connection_hdl hdl)
{
	WebsocketServer::connection_ptr con = server->get_con_from_hdl(hdl);
	string client_ip_port = con->get_remote_endpoint();
	cout << "�ͻ�������: " << client_ip_port << endl;
	curCon = con;
	conns.push_front(con);
}

void OnClose(WebsocketServer* server, websocketpp::connection_hdl hdl)
{
	WebsocketServer::connection_ptr con = server->get_con_from_hdl(hdl);
	string client_ip_port = con->get_remote_endpoint();
	cout << "have client disconnected: " << client_ip_port << endl;
	if (curCon == con) {
		curCon = NULL;
	}
	conns.remove(con);
}

void OnMessage(WebsocketServer* server, websocketpp::connection_hdl hdl, message_ptr msg){
	if (msg->get_payload() == "reconnect device") {
		WebsocketServer::connection_ptr con = server->get_con_from_hdl(hdl);
		deviceCtl->close();
		deviceCtl->connect(0);
		string deviceStatus = deviceCtl->isConnect ? "�豸������" : "δ�����豸";
		con->send(string_To_UTF8(deviceStatus));
	}
}

bool OnPing(WebsocketServer* server, websocketpp::connection_hdl hdl, std::string payload) {
	server->get_alog().write(websocketpp::log::alevel::app, payload);

	WebsocketServer::connection_ptr con = server->get_con_from_hdl(hdl);
	string client_ip_port = con->get_remote_endpoint();

	cout << "recv ping: " << payload << " from " << client_ip_port << endl;
	try {
		server->pong(hdl, "pong");
	}
	catch (websocketpp::exception const& e) {
		cout << "error: " << e.what() << endl;
	}
	return false;
}

bool OnPong(WebsocketServer* server, websocketpp::connection_hdl hdl, std::string payload) {
	server->get_alog().write(websocketpp::log::alevel::app, payload);

	WebsocketServer::connection_ptr con = server->get_con_from_hdl(hdl);
	string client_ip_port = con->get_remote_endpoint();

	cout << "recv pong from " << client_ip_port << ": " << payload << endl;
	return false;
}

// js�ͻ������ӷ�ʽ��var ws = new WebSocket("ws://xxxxx", ["token value"]);
bool OnValidate(WebsocketServer* server, websocketpp::connection_hdl hdl)
{
	WebsocketServer::connection_ptr con = server->get_con_from_hdl(hdl);
	string client_ip_port = con->get_remote_endpoint();
	string key = "Sec-WebSocket-Protocol";
	string token = con->get_request_header(key);
	std::cout << key << ": " << token << std::endl;
	if (0) { // ����������ʱֱ�ӷ���FALSE���ͻ��˻��յ�4��������Ӳ���
		return false;
	}

	// ��֤ͨ�����ͷ��������true
	con->append_header(key, token); // �Ժ�ظ����ݶ�Ҫ�����ͷ����Ϣ
	return true;
}


void initWebsocketServer() {
	server.set_reuse_addr(true); // �����׽���ѡ��SO_REUSEADDR
	// Set logging settings
	server.set_access_channels(websocketpp::log::alevel::all);
	server.clear_access_channels(websocketpp::log::alevel::frame_payload);
	// Initialize ASIO
	server.init_asio();
	server.set_ping_handler(bind(&OnPing, &server, ::_1, ::_2));
	server.set_pong_handler(bind(&OnPong, &server, ::_1, ::_2));
	server.set_open_handler(bind(&OnOpen, &server, ::_1));
	server.set_close_handler(bind(&OnClose, &server, _1));
	server.set_message_handler(bind(&OnMessage, &server, _1, _2));
	server.set_validate_handler(bind(&OnValidate, &server, ::_1));
	//Listen on port 7415
	unsigned short port = 7415;
	try {
		server.listen(port);
		cout << "listen at " << port << endl;
		server.start_accept();
		server.run();
	}
	catch (websocketpp::exception const& e) {
		cout << "error: " << e.what() << endl;
	}
}

void serverCron() {
	while (true) {
		//����Ƿ�����Ӳ���豸
		if (!deviceCtl->isConnect){
			deviceCtl->connect(0);
			if (curCon) {
				string deviceStatus = deviceCtl->isConnect ? "�豸������" : "δ�����豸";
				server.send(curCon->get_handle(), string_To_UTF8(deviceStatus), websocketpp::frame::opcode::text);
			}
		}

		//����Ƿ������֤
		if (curCon && deviceCtl->isConnect) {
			int auth = deviceCtl->authenticate();
			if (auth == 1) {
				server.send(curCon->get_handle(), string_To_UTF8("���ڶ���..."), websocketpp::frame::opcode::text);
				string readStr = deviceCtl->read(idcard);
				if (readStr != "err") {
					server.send(curCon->get_handle(), string_To_UTF8(readStr), websocketpp::frame::opcode::text);
				}
			}
			else if (auth == 0 || auth == 3 || auth == 4) {
				deviceCtl->close();
				server.send(curCon->get_handle(), string_To_UTF8("δ�����豸"), websocketpp::frame::opcode::text);
			}
		}
		
		//�Զ��رշǵ�ǰʹ�õ�����
		list<WebsocketServer::connection_ptr>::iterator iter = conns.begin();
		while (iter != conns.end()){
			WebsocketServer::connection_ptr iCon = *iter;
			if (iCon != curCon){
				iCon->close(cvValue, strReason);
				iter = conns.erase(iter);
			}
			else {
				iter++;
			}
		}
		Sleep(600);
	}
}

int main() {
	thread corn(serverCron);
	corn.detach();
	initWebsocketServer();
	return 0;
}


