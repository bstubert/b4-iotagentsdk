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
#include <TVRemoteScreenSDKCommunication/CommunicationLayerBase/IServiceClient.h>

#include <TVRemoteScreenSDKCommunication/InstantSupportService/InstantSupportData.h>

#include <TVRemoteScreenSDKCommunication/InstantSupportService/InstantSupportError.h>

#include <cstdint>
#include <string>
#include <vector>

namespace TVRemoteScreenSDKCommunication
{

namespace InstantSupportService
{

class IInstantSupportNotificationServiceClient : public IServiceClient
{
public:
	virtual ~IInstantSupportNotificationServiceClient() = default;

	// rpc call NotifyInstantSupportError
	virtual CallStatus NotifyInstantSupportError(const std::string& comId, InstantSupportError errorCode) = 0;

	// rpc call NotifyInstantSupportModified
	virtual CallStatus NotifyInstantSupportModified(const std::string& comId, InstantSupportData data) = 0;
};

} // namespace InstantSupportService

} // namespace TVRemoteScreenSDKCommunication