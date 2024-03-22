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

#include <TVRemoteScreenSDKCommunication/CommunicationLayerBase/CallStatus.h>
#include <TVRemoteScreenSDKCommunication/CommunicationLayerBase/IServiceServer.h>

#include <TVRemoteScreenSDKCommunication/ChatService/Chat.h>

#include <cstdint>
#include <functional>
#include <string>
#include <vector>

namespace TVRemoteScreenSDKCommunication
{

namespace ChatService
{

class IChatOutServiceServer : public IServiceServer
{
public:
	virtual ~IChatOutServiceServer() = default;

	// rpc call ChatCreated
	using ChatCreatedResponseCallback = std::function<void(

		const CallStatus& callStatus)>;
	using ProcessChatCreatedRequestCallback = std::function<void(

		const std::string& comId,
		const std::string& chatId,
		const std::string& title,
		ChatType chatType,
		uint32_t chatTypeId,
		const ChatCreatedResponseCallback& response)>;
	virtual void SetChatCreatedCallback(const ProcessChatCreatedRequestCallback& requestProcessing) = 0;

	// rpc call ChatsRemoved
	using ChatsRemovedResponseCallback = std::function<void(

		const CallStatus& callStatus)>;
	using ProcessChatsRemovedRequestCallback = std::function<void(

		const std::string& comId,
		const std::vector<std::string>& chatId,
		const ChatsRemovedResponseCallback& response)>;
	virtual void SetChatsRemovedCallback(const ProcessChatsRemovedRequestCallback& requestProcessing) = 0;

	// rpc call ReceivedMessages
	using ReceivedMessagesResponseCallback = std::function<void(

		const CallStatus& callStatus)>;
	using ProcessReceivedMessagesRequestCallback = std::function<void(

		const std::string& comId,
		const std::vector<ReceivedMessage>& received,
		const ReceivedMessagesResponseCallback& response)>;
	virtual void SetReceivedMessagesCallback(const ProcessReceivedMessagesRequestCallback& requestProcessing) = 0;

	// rpc call MessageSent
	using MessageSentResponseCallback = std::function<void(

		const CallStatus& callStatus)>;
	using ProcessMessageSentRequestCallback = std::function<void(

		const std::string& comId,
		uint32_t localId,
		const std::string& messageId,
		uint64_t timeStamp,
		const MessageSentResponseCallback& response)>;
	virtual void SetMessageSentCallback(const ProcessMessageSentRequestCallback& requestProcessing) = 0;

	// rpc call MessageNotSent
	using MessageNotSentResponseCallback = std::function<void(

		const CallStatus& callStatus)>;
	using ProcessMessageNotSentRequestCallback = std::function<void(

		const std::string& comId,
		uint32_t localId,
		const MessageNotSentResponseCallback& response)>;
	virtual void SetMessageNotSentCallback(const ProcessMessageNotSentRequestCallback& requestProcessing) = 0;

	// rpc call LoadedMessages
	using LoadedMessagesResponseCallback = std::function<void(

		const CallStatus& callStatus)>;
	using ProcessLoadedMessagesRequestCallback = std::function<void(

		const std::string& comId,
		const std::vector<ReceivedMessage>& messages,
		bool hasMore,
		const LoadedMessagesResponseCallback& response)>;
	virtual void SetLoadedMessagesCallback(const ProcessLoadedMessagesRequestCallback& requestProcessing) = 0;

	// rpc call DeletedHistory
	using DeletedHistoryResponseCallback = std::function<void(

		const CallStatus& callStatus)>;
	using ProcessDeletedHistoryRequestCallback = std::function<void(

		const std::string& comId,
		const std::string& chatId,
		const DeletedHistoryResponseCallback& response)>;
	virtual void SetDeletedHistoryCallback(const ProcessDeletedHistoryRequestCallback& requestProcessing) = 0;

	// rpc call ClosedChat
	using ClosedChatResponseCallback = std::function<void(

		const CallStatus& callStatus)>;
	using ProcessClosedChatRequestCallback = std::function<void(

		const std::string& comId,
		const std::string& chatId,
		const ClosedChatResponseCallback& response)>;
	virtual void SetClosedChatCallback(const ProcessClosedChatRequestCallback& requestProcessing) = 0;
};

} // namespace ChatService

} // namespace TVRemoteScreenSDKCommunication