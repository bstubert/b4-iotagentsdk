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

#include "ChatInServicegRPCClient.h"

#include <TVRemoteScreenSDKCommunication/ServiceBase/ClientErrorMessage.h>
#include <TVRemoteScreenSDKCommunication/ServiceBase/RequestMetadata.h>

#include <grpc++/create_channel.h>

namespace TVRemoteScreenSDKCommunication
{

namespace ChatService
{

void ChatInServicegRPCClient::StartClient(const std::string& destination)
{
	m_destination = destination;

	m_channel = ::grpc::CreateChannel(m_destination, ::grpc::InsecureChannelCredentials());
	m_stub = ::tvchatservice::ChatInService::NewStub(m_channel);
}

void ChatInServicegRPCClient::StopClient(bool /*force*/)
{
	m_stub.reset();
	m_channel.reset();
}

ServiceType ChatInServicegRPCClient::GetServiceType() const
{
	return ServiceType::ChatIn;
}

const std::string& ChatInServicegRPCClient::GetDestination() const
{
	return m_destination;
}

// rpc call ObtainChats
auto ChatInServicegRPCClient::ObtainChats(const std::string& comId) -> ObtainChatsResponse
{
	ObtainChatsResponse returnValue{};

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

	::tvchatservice::ObtainChatsRequest request{};

	::tvchatservice::ObtainChatsResponse response{};

	::grpc::Status status = m_stub->ObtainChats(&context, request, &response);

	if (status.ok())
	{
		returnValue.state = CallState::Ok;

		std::vector<ChatInfo> chats(response.chatinfo_size());

		for (int index = 0; index < response.chatinfo_size(); ++index)
		{
			const ::tvchatservice::ChatInfo& info = response.chatinfo(index);

			chats[index].chatId = info.chatid();
			chats[index].title = info.title();
			chats[index].chatTypeId = info.chattypeid();

			const auto chatType = info.chattype();
			const auto chatState = info.chatstate();

			ChatType chatTypeEnumValue = ChatType::Machine;
			bool chatTypeConverted = true;
			switch (chatType)
			{
				case ::tvchatservice::ChatType::Machine:
					chatTypeEnumValue = ChatType::Machine;
					break;
				case ::tvchatservice::ChatType::Session:
					chatTypeEnumValue = ChatType::Session;
					break;
				default:
					chatTypeConverted = false;
					break;
			}

			ChatState chatStateEnumValue = ChatState::Open;
			bool chatStateConverted = true;
			switch (chatState)
			{
				case ::tvchatservice::ChatState::Open:
					chatStateEnumValue = ChatState::Open;
					break;
				case ::tvchatservice::ChatState::Closed:
					chatStateEnumValue = ChatState::Closed;
					break;
				default:
					chatStateConverted = false;
					break;
			}

			if (!chatTypeConverted || !chatStateConverted)
			{
				returnValue.errorMessage = TvServiceBase::ErrorMessage_InvalidResponseValue;
				return returnValue;
			}
			chats[index].chatType = chatTypeEnumValue;
			chats[index].chatState = chatStateEnumValue;
		}

		returnValue.chats.swap(chats);
	}
	else
	{
		returnValue.errorMessage = status.error_message();
	}

	return returnValue;
}

// rpc call SelectChat
auto ChatInServicegRPCClient::SelectChat(const std::string& comId, const std::string& chatId) -> CallStatus
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

	::tvchatservice::SelectChatRequest request{};

	request.set_chatid(chatId);

	::tvchatservice::SelectChatResponse response{};

	::grpc::Status status = m_stub->SelectChat(&context, request, &response);

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

// rpc call SendMessage
auto ChatInServicegRPCClient::SendMessage(const std::string& comId, uint32_t localId, const std::string& content) -> CallStatus
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

	::tvchatservice::SendMessageRequest request{};

	request.set_localid(localId);

	request.set_content(content);

	::tvchatservice::SendMessageResponse response{};

	::grpc::Status status = m_stub->SendMessage(&context, request, &response);

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

// rpc call LoadMessages
auto ChatInServicegRPCClient::LoadMessages(const std::string& comId, uint32_t count, const std::string& lastId) -> CallStatus
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
	if (count == 0)
	{
		returnValue.errorMessage = TvServiceBase::ErrorMessage_InvalidInputParameter;
		return returnValue;
	}

	::grpc::ClientContext context{};

	context.AddMetadata(ServiceBase::CommunicationIdToken, comId);

	::tvchatservice::LoadMessagesRequest request{};

	request.set_count(count);

	request.set_lastid(lastId);

	::tvchatservice::LoadMessagesResponse response{};

	::grpc::Status status = m_stub->LoadMessages(&context, request, &response);

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

// rpc call DeleteHistory
auto ChatInServicegRPCClient::DeleteHistory(const std::string& comId) -> CallStatus
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

	::tvchatservice::DeleteHistoryRequest request{};

	::tvchatservice::DeleteHistoryResponse response{};

	::grpc::Status status = m_stub->DeleteHistory(&context, request, &response);

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

// rpc call DeleteChat
auto ChatInServicegRPCClient::DeleteChat(const std::string& comId) -> CallStatus
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

	::tvchatservice::DeleteChatRequest request{};

	::tvchatservice::DeleteChatResponse response{};

	::grpc::Status status = m_stub->DeleteChat(&context, request, &response);

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

} // namespace ChatService

} // namespace TVRemoteScreenSDKCommunication