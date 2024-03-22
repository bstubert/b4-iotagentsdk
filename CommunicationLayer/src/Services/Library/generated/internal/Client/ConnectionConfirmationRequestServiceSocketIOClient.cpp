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

#include "ConnectionConfirmationRequestServiceSocketIOClient.h"

#include <TVRemoteScreenSDKCommunication/ServiceBase/ClientErrorMessage.h>
#include <TVRemoteScreenSDKCommunication/ServiceBase/RequestMetadata.h>

#include "internal/ConnectionConfirmationRequestServiceRequestFunctions.h"

#include "ConnectionConfirmationRequestMessages.pb.h"

namespace TVRemoteScreenSDKCommunication
{

namespace ConnectionConfirmationService
{

void ConnectionConfirmationRequestServiceSocketIOClient::StartClient(const std::string& destination)
{
	m_destination = destination;

	m_channel.reset(new Transport::SocketIO::ChannelInterface(m_destination));
}

void ConnectionConfirmationRequestServiceSocketIOClient::StopClient(bool /*force*/)
{
	m_channel.reset();
}

ServiceType ConnectionConfirmationRequestServiceSocketIOClient::GetServiceType() const
{
	return ServiceType::ConnectionConfirmationRequest;
}

const std::string& ConnectionConfirmationRequestServiceSocketIOClient::GetDestination() const
{
	return m_destination;
}

// rpc call RequestConnectionConfirmation
auto ConnectionConfirmationRequestServiceSocketIOClient::RequestConnectionConfirmation(const std::string& comId,
	ConnectionType connectionType) -> CallStatus
{
	CallStatus returnValue{};

	if (m_channel == nullptr)
	{
		returnValue.errorMessage = TvServiceBase::ErrorMessage_MissingStartClient;
		return returnValue;
	}

	if (comId.empty())
	{
		returnValue.errorMessage = TvServiceBase::ErrorMessage_InvalidInputParameter;
		return returnValue;
	}

	::tvconnectionconfirmationservice::RequestConnectionConfirmationRequest request{};

	::tvconnectionconfirmationservice::RequestConnectionConfirmationRequest_ConnectionType connectionTypeProtoValue =
		::tvconnectionconfirmationservice::RequestConnectionConfirmationRequest_ConnectionType_Undefined;

	switch (connectionType)
	{
		case ConnectionType::Undefined:
			connectionTypeProtoValue =
				::tvconnectionconfirmationservice::RequestConnectionConfirmationRequest_ConnectionType_Undefined;
			break;
		case ConnectionType::InstantSupport:
			connectionTypeProtoValue =
				::tvconnectionconfirmationservice::RequestConnectionConfirmationRequest_ConnectionType_InstantSupport;
			break;
		default:

			break;
	}

	request.set_connectiontype(connectionTypeProtoValue);

	::tvconnectionconfirmationservice::RequestConnectionConfirmationResponse response{};

	Transport::SocketIO::Status status = m_channel->Call(comId, Function_RequestConnectionConfirmation, request, response);

	if (status.ok())
	{
		returnValue = CallStatus{CallState::Ok};
	}
	else
	{
		returnValue.errorMessage = status.error_message();
	}

	return returnValue;
}

} // namespace ConnectionConfirmationService

} // namespace TVRemoteScreenSDKCommunication