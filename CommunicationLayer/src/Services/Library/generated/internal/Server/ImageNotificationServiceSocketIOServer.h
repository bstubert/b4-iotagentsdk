//********************************************************************************//
// MIT License                                                                    //
//                                                                                //
// Copyright (c) 2024 TeamViewer Germany GmbH                                     //
//                                                                                //
// Permission is hereby granted, free of charge, to any person obtaining a copy   //
// of this software and associated documentation files (the "Software"), to deal  //
// in the Software without restriction, including without limitation the rights   //
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell      //
// copies of the Software, and to permit persons to whom the Software is          //
// furnished to do so, subject to the following conditions:                       //
//                                                                                //
// The above copyright notice and this permission notice shall be included in all //
// copies or substantial portions of the Software.                                //
//                                                                                //
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR     //
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,       //
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE    //
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER         //
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,  //
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE  //
// SOFTWARE.                                                                      //
//********************************************************************************//
// ==================================
// Generated by TVCMGen. DO NOT EDIT!
// ==================================
#pragma once

#include <TVRemoteScreenSDKCommunication/ImageNotificationService/IImageNotificationServiceServer.h>
#include <TVRemoteScreenSDKCommunication/ServiceBase/SocketIOTransport.h>

#include <memory>
#include <string>

namespace TVRemoteScreenSDKCommunication
{

namespace ImageNotificationService
{

class ImageNotificationServiceSocketIOServer : public IImageNotificationServiceServer
{
public:
	using TransportFW = Transport::TCPSocket;

	ImageNotificationServiceSocketIOServer() = default;
	~ImageNotificationServiceSocketIOServer() override = default;

	bool StartServer(const std::string& location) override;
	void StopServer(bool force) override;

	ServiceType GetServiceType() const override;
	const std::string& GetLocation() const override;

	// public interface impl
	void SetUpdateImageDefinitionCallback(const ProcessUpdateImageDefinitionRequestCallback& requestProcessing) override;

	void SetNotifiyImageChangedCallback(const ProcessNotifiyImageChangedRequestCallback& requestProcessing) override;

private:
	std::string m_location;
	std::unique_ptr<Transport::SocketIO::Server> m_server;

	ProcessUpdateImageDefinitionRequestCallback m_UpdateImageDefinitionProcessing;
	ProcessNotifiyImageChangedRequestCallback m_NotifiyImageChangedProcessing;
};

} // namespace ImageNotificationService

} // namespace TVRemoteScreenSDKCommunication