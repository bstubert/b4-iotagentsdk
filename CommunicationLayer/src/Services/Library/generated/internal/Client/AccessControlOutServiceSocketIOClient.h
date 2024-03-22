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

#include <TVRemoteScreenSDKCommunication/AccessControlService/IAccessControlOutServiceClient.h>
#include <TVRemoteScreenSDKCommunication/ServiceBase/SocketIOTransport.h>

#include <TVRemoteScreenSDKCommunication/ServiceBase/SocketIO/ChannelInterface.h>

#include <memory>
#include <string>

namespace TVRemoteScreenSDKCommunication
{

namespace AccessControlService
{

class AccessControlOutServiceSocketIOClient : public IAccessControlOutServiceClient
{
public:
	using TransportFW = Transport::TCPSocket;

	AccessControlOutServiceSocketIOClient() = default;
	~AccessControlOutServiceSocketIOClient() override = default;

	void StartClient(const std::string& destination) override;
	void StopClient(bool force) override;

	ServiceType GetServiceType() const override;
	const std::string& GetDestination() const override;

	// rpc call AskForConfirmation

	CallStatus AskForConfirmation(

		const std::string& comId,
		AccessControl feature,
		uint32_t timeout) override;

	// rpc call NotifyChange

	CallStatus NotifyChange(

		const std::string& comId,
		AccessControl feature,
		Access access) override;

private:
	std::string m_destination;
	std::unique_ptr<TransportFW::ChannelInterface> m_channel;
};

} // namespace AccessControlService

} // namespace TVRemoteScreenSDKCommunication