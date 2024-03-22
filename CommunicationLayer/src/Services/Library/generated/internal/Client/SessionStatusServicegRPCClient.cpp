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

#include "SessionStatusServicegRPCClient.h"

#include <TVRemoteScreenSDKCommunication/ServiceBase/ClientErrorMessage.h>
#include <TVRemoteScreenSDKCommunication/ServiceBase/RequestMetadata.h>

#include <grpc++/create_channel.h>

namespace TVRemoteScreenSDKCommunication
{

namespace SessionStatusService
{

void SessionStatusServicegRPCClient::StartClient(const std::string& destination)
{
	m_destination = destination;

	m_channel = ::grpc::CreateChannel(m_destination, ::grpc::InsecureChannelCredentials());
	m_stub = ::tvsessionstatusservice::SessionStatusService::NewStub(m_channel);
}

void SessionStatusServicegRPCClient::StopClient(bool /*force*/)
{
	m_stub.reset();
	m_channel.reset();
}

ServiceType SessionStatusServicegRPCClient::GetServiceType() const
{
	return ServiceType::SessionStatus;
}

const std::string& SessionStatusServicegRPCClient::GetDestination() const
{
	return m_destination;
}

// rpc call RemoteControlStarted
auto SessionStatusServicegRPCClient::RemoteControlStarted(const std::string& comId, GrabStrategy strategy) -> CallStatus
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

	::tvsessionstatusservice::RemoteControlStartedRequest request{};

	::tvsessionstatusservice::RemoteControlStartedRequest_GrabStrategy strategyProtoValue =
		::tvsessionstatusservice::RemoteControlStartedRequest_GrabStrategy_Unknown;

	switch (strategy)
	{
		case GrabStrategy::Unknown:
			strategyProtoValue = ::tvsessionstatusservice::RemoteControlStartedRequest_GrabStrategy_Unknown;
			break;
		case GrabStrategy::NoGrabbing:
			strategyProtoValue = ::tvsessionstatusservice::RemoteControlStartedRequest_GrabStrategy_NoGrabbing;
			break;
		case GrabStrategy::EventDrivenByApp:
			strategyProtoValue = ::tvsessionstatusservice::RemoteControlStartedRequest_GrabStrategy_EventDrivenByApp;
			break;
		case GrabStrategy::ChangeNotificationOnly:
			strategyProtoValue = ::tvsessionstatusservice::RemoteControlStartedRequest_GrabStrategy_ChangeNotificationOnly;
			break;
		default:

			break;
	}

	request.set_strategy(strategyProtoValue);

	::tvsessionstatusservice::RemoteControlStartedResponse response{};

	::grpc::Status status = m_stub->RemoteControlStarted(&context, request, &response);

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

// rpc call RemoteControlStopped
auto SessionStatusServicegRPCClient::RemoteControlStopped(const std::string& comId) -> CallStatus
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

	::tvsessionstatusservice::RemoteControlStoppedRequest request{};

	::tvsessionstatusservice::RemoteControlStoppedResponse response{};

	::grpc::Status status = m_stub->RemoteControlStopped(&context, request, &response);

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

// rpc call TVSessionStarted
auto SessionStatusServicegRPCClient::TVSessionStarted(const std::string& comId, int32_t tvSessionID, int32_t tvSessionsCount) -> CallStatus
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

	::tvsessionstatusservice::TVSessionStartedRequest request{};

	request.set_tvsessionid(tvSessionID);

	request.set_tvsessionscount(tvSessionsCount);

	::tvsessionstatusservice::TVSessionStartedResponse response{};

	::grpc::Status status = m_stub->TVSessionStarted(&context, request, &response);

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

// rpc call TVSessionStopped
auto SessionStatusServicegRPCClient::TVSessionStopped(const std::string& comId, int32_t tvSessionID, int32_t tvSessionsCount) -> CallStatus
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

	::tvsessionstatusservice::TVSessionStoppedRequest request{};

	request.set_tvsessionid(tvSessionID);

	request.set_tvsessionscount(tvSessionsCount);

	::tvsessionstatusservice::TVSessionStoppedResponse response{};

	::grpc::Status status = m_stub->TVSessionStopped(&context, request, &response);

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

} // namespace SessionStatusService

} // namespace TVRemoteScreenSDKCommunication