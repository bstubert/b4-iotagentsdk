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

#include "ConnectionConfirmationResponseServiceSocketIOClient.h"

#include <TVRemoteScreenSDKCommunication/ServiceBase/ClientErrorMessage.h>
#include <TVRemoteScreenSDKCommunication/ServiceBase/RequestMetadata.h>

#include "internal/ConnectionConfirmationResponseServiceResponseFunctions.h"

#include "ConnectionConfirmationResponseMessages.pb.h"

namespace TVRemoteScreenSDKCommunication
{

namespace ConnectionConfirmationService
{

void ConnectionConfirmationResponseServiceSocketIOClient::StartClient(const std::string& destination)
{
	m_destination = destination;

	m_channel.reset(new Transport::SocketIO::ChannelInterface(m_destination));
}

void ConnectionConfirmationResponseServiceSocketIOClient::StopClient(bool /*force*/)
{
	m_channel.reset();
}

ServiceType ConnectionConfirmationResponseServiceSocketIOClient::GetServiceType() const
{
	return ServiceType::ConnectionConfirmationResponse;
}

const std::string& ConnectionConfirmationResponseServiceSocketIOClient::GetDestination() const
{
	return m_destination;
}

// rpc call ConfirmConnectionRequest
auto ConnectionConfirmationResponseServiceSocketIOClient::ConfirmConnectionRequest(const std::string& comId,
	ConnectionType connectionType,
	ConnectionUserConfirmation confirmation) -> CallStatus
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

	::tvconnectionconfirmationservice::ConfirmConnectionRequestRequest request{};

	::tvconnectionconfirmationservice::ConfirmConnectionRequestRequest_ConnectionType connectionTypeProtoValue =
		::tvconnectionconfirmationservice::ConfirmConnectionRequestRequest_ConnectionType_Undefined;

	switch (connectionType)
	{
		case ConnectionType::Undefined:
			connectionTypeProtoValue = ::tvconnectionconfirmationservice::ConfirmConnectionRequestRequest_ConnectionType_Undefined;
			break;
		case ConnectionType::InstantSupport:
			connectionTypeProtoValue =
				::tvconnectionconfirmationservice::ConfirmConnectionRequestRequest_ConnectionType_InstantSupport;
			break;
		default:

			break;
	}

	request.set_connectiontype(connectionTypeProtoValue);

	::tvconnectionconfirmationservice::ConfirmConnectionRequestRequest_ConnectionUserConfirmation confirmationProtoValue =
		::tvconnectionconfirmationservice::ConfirmConnectionRequestRequest_ConnectionUserConfirmation_NoResponse;

	switch (confirmation)
	{
		case ConnectionUserConfirmation::NoResponse:
			confirmationProtoValue =
				::tvconnectionconfirmationservice::ConfirmConnectionRequestRequest_ConnectionUserConfirmation_NoResponse;
			break;
		case ConnectionUserConfirmation::Accepted:
			confirmationProtoValue =
				::tvconnectionconfirmationservice::ConfirmConnectionRequestRequest_ConnectionUserConfirmation_Accepted;
			break;
		case ConnectionUserConfirmation::Denied:
			confirmationProtoValue =
				::tvconnectionconfirmationservice::ConfirmConnectionRequestRequest_ConnectionUserConfirmation_Denied;
			break;
		default:

			break;
	}

	request.set_confirmation(confirmationProtoValue);

	::tvconnectionconfirmationservice::ConfirmConnectionRequestResponse response{};

	Transport::SocketIO::Status status = m_channel->Call(comId, Function_ConfirmConnectionRequest, request, response);

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