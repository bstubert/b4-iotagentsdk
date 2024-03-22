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

#include "InstantSupportNotificationServicegRPCClient.h"

#include <TVRemoteScreenSDKCommunication/ServiceBase/ClientErrorMessage.h>
#include <TVRemoteScreenSDKCommunication/ServiceBase/RequestMetadata.h>

#include <grpc++/create_channel.h>

namespace TVRemoteScreenSDKCommunication
{

namespace InstantSupportService
{

void InstantSupportNotificationServicegRPCClient::StartClient(const std::string& destination)
{
	m_destination = destination;

	m_channel = ::grpc::CreateChannel(m_destination, ::grpc::InsecureChannelCredentials());
	m_stub = ::tvinstantsupportservice::InstantSupportNotificationService::NewStub(m_channel);
}

void InstantSupportNotificationServicegRPCClient::StopClient(bool /*force*/)
{
	m_stub.reset();
	m_channel.reset();
}

ServiceType InstantSupportNotificationServicegRPCClient::GetServiceType() const
{
	return ServiceType::InstantSupportNotification;
}

const std::string& InstantSupportNotificationServicegRPCClient::GetDestination() const
{
	return m_destination;
}

// rpc call NotifyInstantSupportError
auto InstantSupportNotificationServicegRPCClient::NotifyInstantSupportError(const std::string& comId,
	InstantSupportError errorCode) -> CallStatus
{
	CallStatus returnValue{};

	if (m_channel == nullptr || m_stub == nullptr)
	{
		returnValue.errorMessage = TvServiceBase::ErrorMessage_MissingStartClient;
		return returnValue;
	}

	if (comId.empty())
	{
		returnValue.errorMessage = TvServiceBase::ErrorMessage_InvalidInputParameter;
		return returnValue;
	}

	::grpc::ClientContext context{};

	context.AddMetadata(ServiceBase::CommunicationIdToken, comId);

	::tvinstantsupportservice::ErrorNotificationRequest request{};

	::tvinstantsupportservice::ErrorNotificationRequest_ErrorCode errorCodeProtoValue =
		::tvinstantsupportservice::ErrorNotificationRequest_ErrorCode_InternalError;

	switch (errorCode)
	{
		case InstantSupportError::InternalError:
			errorCodeProtoValue = ::tvinstantsupportservice::ErrorNotificationRequest_ErrorCode_InternalError;
			break;
		case InstantSupportError::InvalidToken:
			errorCodeProtoValue = ::tvinstantsupportservice::ErrorNotificationRequest_ErrorCode_InvalidToken;
			break;
		case InstantSupportError::InvalidGroup:
			errorCodeProtoValue = ::tvinstantsupportservice::ErrorNotificationRequest_ErrorCode_InvalidGroup;
			break;
		case InstantSupportError::InvalidSessionCode:
			errorCodeProtoValue = ::tvinstantsupportservice::ErrorNotificationRequest_ErrorCode_InvalidSessionCode;
			break;
		case InstantSupportError::Busy:
			errorCodeProtoValue = ::tvinstantsupportservice::ErrorNotificationRequest_ErrorCode_Busy;
			break;
		case InstantSupportError::InvalidEmail:
			errorCodeProtoValue = ::tvinstantsupportservice::ErrorNotificationRequest_ErrorCode_InvalidEmail;
			break;
		default:

			break;
	}

	request.set_errorcode(errorCodeProtoValue);

	::tvinstantsupportservice::ErrorNotificationResponse response{};

	::grpc::Status status = m_stub->NotifyInstantSupportError(&context, request, &response);

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

// rpc call NotifyInstantSupportModified
auto InstantSupportNotificationServicegRPCClient::NotifyInstantSupportModified(const std::string& comId,
	InstantSupportData data) -> CallStatus
{
	CallStatus returnValue{};

	if (m_channel == nullptr || m_stub == nullptr)
	{
		returnValue.errorMessage = TvServiceBase::ErrorMessage_MissingStartClient;
		return returnValue;
	}

	if (comId.empty())
	{
		returnValue.errorMessage = TvServiceBase::ErrorMessage_InvalidInputParameter;
		return returnValue;
	}

	::grpc::ClientContext context{};

	context.AddMetadata(ServiceBase::CommunicationIdToken, comId);

	::tvinstantsupportservice::ModifiedNotificationRequest request{};

	const auto state = data.state;

	::tvinstantsupportservice::ModifiedNotificationRequest_InstantSupportState stateProtoValue =
		::tvinstantsupportservice::ModifiedNotificationRequest_InstantSupportState_Undefined;

	switch (state)
	{
		case InstantSupportState::Undefined:
			stateProtoValue = ::tvinstantsupportservice::ModifiedNotificationRequest_InstantSupportState_Undefined;
			break;
		case InstantSupportState::Open:
			stateProtoValue = ::tvinstantsupportservice::ModifiedNotificationRequest_InstantSupportState_Open;
			break;
		case InstantSupportState::Closed:
			stateProtoValue = ::tvinstantsupportservice::ModifiedNotificationRequest_InstantSupportState_Closed;
			break;
		default:

			break;
	}

	request.set_sessioncode(data.sessionCode);
	request.set_name(data.name);
	request.set_description(data.description);
	request.set_state(stateProtoValue);

	::tvinstantsupportservice::ModifiedNotificationResponse response{};

	::grpc::Status status = m_stub->NotifyInstantSupportModified(&context, request, &response);

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

} // namespace InstantSupportService

} // namespace TVRemoteScreenSDKCommunication