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

#include <TVRemoteScreenSDKCommunication/ViewGeometryService/VirtualDesktop.h>

#include <cstdint>
#include <functional>
#include <string>
#include <vector>

namespace TVRemoteScreenSDKCommunication
{

namespace ViewGeometryService
{

class IViewGeometryServiceServer : public IServiceServer
{
public:
	virtual ~IViewGeometryServiceServer() = default;

	// rpc call UpdateAreaOfInterest
	using UpdateAreaOfInterestResponseCallback = std::function<void(const CallStatus& callStatus)>;
	using ProcessUpdateAreaOfInterestRequestCallback =
		std::function<void(const std::string& comId, const Rect& rect, const UpdateAreaOfInterestResponseCallback& response)>;
	virtual void SetUpdateAreaOfInterestCallback(const ProcessUpdateAreaOfInterestRequestCallback& requestProcessing) = 0;

	// rpc call UpdateVirtualDesktop
	using UpdateVirtualDesktopResponseCallback = std::function<void(const CallStatus& callStatus)>;
	using ProcessUpdateVirtualDesktopRequestCallback =
		std::function<void(const std::string& comId, const VirtualDesktop& virtualDesktop, const UpdateVirtualDesktopResponseCallback& response)>;
	virtual void SetUpdateVirtualDesktopCallback(const ProcessUpdateVirtualDesktopRequestCallback& requestProcessing) = 0;
};

} // namespace ViewGeometryService

} // namespace TVRemoteScreenSDKCommunication