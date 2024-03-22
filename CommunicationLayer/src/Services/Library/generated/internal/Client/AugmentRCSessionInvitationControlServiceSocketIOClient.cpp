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

#include "AugmentRCSessionInvitationControlServiceSocketIOClient.h"

#include <TVRemoteScreenSDKCommunication/ServiceBase/ClientErrorMessage.h>
#include <TVRemoteScreenSDKCommunication/ServiceBase/RequestMetadata.h>

#include "internal/AugmentRCSessionInvitationControlServiceControlFunctions.h"

#include "AugmentRCSessionInvitation.pb.h"
#include "AugmentRCSessionInvitationControlMessages.pb.h"

namespace TVRemoteScreenSDKCommunication
{

namespace AugmentRCSessionInvitationService
{

void AugmentRCSessionInvitationControlServiceSocketIOClient::StartClient(const std::string& destination)
{
	m_destination = destination;

	m_channel.reset(new Transport::SocketIO::ChannelInterface(m_destination));
}

void AugmentRCSessionInvitationControlServiceSocketIOClient::StopClient(bool /*force*/)
{
	m_channel.reset();
}

ServiceType AugmentRCSessionInvitationControlServiceSocketIOClient::GetServiceType() const
{
	return ServiceType::AugmentRCSessionInvitationControl;
}

const std::string& AugmentRCSessionInvitationControlServiceSocketIOClient::GetDestination() const
{
	return m_destination;
}

// rpc call StartListening
auto AugmentRCSessionInvitationControlServiceSocketIOClient::StartListening(const std::string& comId) -> CallStatus
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

	::tvaugmentrcsessioninvitationservice::StartListeningRequest request{};

	::tvaugmentrcsessioninvitationservice::StartListeningResponse response{};

	Transport::SocketIO::Status status = m_channel->Call(comId, Function_StartListening, request, response);

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

// rpc call StopListening
auto AugmentRCSessionInvitationControlServiceSocketIOClient::StopListening(const std::string& comId) -> CallStatus
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

	::tvaugmentrcsessioninvitationservice::StopListeningRequest request{};

	::tvaugmentrcsessioninvitationservice::StopListeningResponse response{};

	Transport::SocketIO::Status status = m_channel->Call(comId, Function_StopListening, request, response);

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

// rpc call CancelReceivedInvitation
auto AugmentRCSessionInvitationControlServiceSocketIOClient::CancelReceivedInvitation(const std::string& comId,
	CancellationReason cancellationReason) -> CallStatus
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

	::tvaugmentrcsessioninvitationservice::CancelReceivedInvitationRequest request{};

	::tvaugmentrcsessioninvitationservice::CancellationReason cancellationReasonProtoValue =
		::tvaugmentrcsessioninvitationservice::CancellationReason::Invalid;

	switch (cancellationReason)
	{
		case CancellationReason::Invalid:
			cancellationReasonProtoValue = ::tvaugmentrcsessioninvitationservice::CancellationReason::Invalid;
			break;
		case CancellationReason::ClosedDialog:
			cancellationReasonProtoValue = ::tvaugmentrcsessioninvitationservice::CancellationReason::ClosedDialog;
			break;
		case CancellationReason::PressedCancelButton:
			cancellationReasonProtoValue = ::tvaugmentrcsessioninvitationservice::CancellationReason::PressedCancelButton;
			break;
		default:

			break;
	}

	request.set_cancellationreason(cancellationReasonProtoValue);

	::tvaugmentrcsessioninvitationservice::CancelReceivedInvitationResponse response{};

	Transport::SocketIO::Status status = m_channel->Call(comId, Function_CancelReceivedInvitation, request, response);

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

} // namespace AugmentRCSessionInvitationService

} // namespace TVRemoteScreenSDKCommunication