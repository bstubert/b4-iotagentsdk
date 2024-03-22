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

#include "AccessControlOutServiceSocketIOClient.h"

#include <TVRemoteScreenSDKCommunication/ServiceBase/ClientErrorMessage.h>
#include <TVRemoteScreenSDKCommunication/ServiceBase/RequestMetadata.h>

#include "internal/AccessControlOutServiceOutFunctions.h"

#include "AccessControl.pb.h"
#include "AccessControlOutMessages.pb.h"

namespace TVRemoteScreenSDKCommunication
{

namespace AccessControlService
{

void AccessControlOutServiceSocketIOClient::StartClient(const std::string& destination)
{
	m_destination = destination;

	m_channel.reset(new Transport::SocketIO::ChannelInterface(m_destination));
}

void AccessControlOutServiceSocketIOClient::StopClient(bool /*force*/)
{
	m_channel.reset();
}

ServiceType AccessControlOutServiceSocketIOClient::GetServiceType() const
{
	return ServiceType::AccessControlOut;
}

const std::string& AccessControlOutServiceSocketIOClient::GetDestination() const
{
	return m_destination;
}

// rpc call AskForConfirmation
auto AccessControlOutServiceSocketIOClient::AskForConfirmation(const std::string& comId, AccessControl feature, uint32_t timeout)
	-> CallStatus
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

	::tvaccesscontrolservice::AskForConfirmationRequest request{};

	::tvaccesscontrolservice::AccessControl featureProtoValue = ::tvaccesscontrolservice::AccessControl::FileTransfer;
	bool featureConverted = true;
	switch (feature)
	{
		case AccessControl::FileTransfer:
			featureProtoValue = ::tvaccesscontrolservice::AccessControl::FileTransfer;
			break;
		case AccessControl::RemoteView:
			featureProtoValue = ::tvaccesscontrolservice::AccessControl::RemoteView;
			break;
		case AccessControl::RemoteControl:
			featureProtoValue = ::tvaccesscontrolservice::AccessControl::RemoteControl;
			break;
		case AccessControl::ScreenRecording:
			featureProtoValue = ::tvaccesscontrolservice::AccessControl::ScreenRecording;
			break;
		default:
			featureConverted = false;
			break;
	}

	if (!featureConverted)
	{
		returnValue.errorMessage = TvServiceBase::ErrorMessage_InvalidInputParameter;
		return returnValue;
	}

	request.set_feature(featureProtoValue);

	request.set_timeout(timeout);

	::tvaccesscontrolservice::AskForConfirmationResponse response{};

	Transport::SocketIO::Status status = m_channel->Call(comId, Function_AskForConfirmation, request, response);

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

// rpc call NotifyChange
auto AccessControlOutServiceSocketIOClient::NotifyChange(const std::string& comId, AccessControl feature, Access access) -> CallStatus
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

	::tvaccesscontrolservice::NotifyChangeRequest request{};

	::tvaccesscontrolservice::AccessControl featureProtoValue = ::tvaccesscontrolservice::AccessControl::FileTransfer;
	bool featureConverted = true;
	switch (feature)
	{
		case AccessControl::FileTransfer:
			featureProtoValue = ::tvaccesscontrolservice::AccessControl::FileTransfer;
			break;
		case AccessControl::RemoteView:
			featureProtoValue = ::tvaccesscontrolservice::AccessControl::RemoteView;
			break;
		case AccessControl::RemoteControl:
			featureProtoValue = ::tvaccesscontrolservice::AccessControl::RemoteControl;
			break;
		case AccessControl::ScreenRecording:
			featureProtoValue = ::tvaccesscontrolservice::AccessControl::ScreenRecording;
			break;
		default:
			featureConverted = false;
			break;
	}

	if (!featureConverted)
	{
		returnValue.errorMessage = TvServiceBase::ErrorMessage_InvalidInputParameter;
		return returnValue;
	}

	request.set_feature(featureProtoValue);

	::tvaccesscontrolservice::Access accessProtoValue = ::tvaccesscontrolservice::Access::Allowed;
	bool accessConverted = true;
	switch (access)
	{
		case Access::Allowed:
			accessProtoValue = ::tvaccesscontrolservice::Access::Allowed;
			break;
		case Access::AfterConfirmation:
			accessProtoValue = ::tvaccesscontrolservice::Access::AfterConfirmation;
			break;
		case Access::Denied:
			accessProtoValue = ::tvaccesscontrolservice::Access::Denied;
			break;
		default:
			accessConverted = false;
			break;
	}

	if (!accessConverted)
	{
		returnValue.errorMessage = TvServiceBase::ErrorMessage_InvalidInputParameter;
		return returnValue;
	}

	request.set_access(accessProtoValue);

	::tvaccesscontrolservice::NotifyChangeResponse response{};

	Transport::SocketIO::Status status = m_channel->Call(comId, Function_NotifyChange, request, response);

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

} // namespace AccessControlService

} // namespace TVRemoteScreenSDKCommunication