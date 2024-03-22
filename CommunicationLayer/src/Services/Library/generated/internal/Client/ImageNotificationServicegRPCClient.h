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

#include <TVRemoteScreenSDKCommunication/ImageNotificationService/IImageNotificationServiceClient.h>
#include <TVRemoteScreenSDKCommunication/ServiceBase/gRPCTransport.h>

#include "ImageNotificationService.grpc.pb.h"
#include <memory>
#include <string>

namespace TVRemoteScreenSDKCommunication
{

namespace ImageNotificationService
{

class ImageNotificationServicegRPCClient : public IImageNotificationServiceClient
{
public:
	using TransportFW = Transport::gRPC;

	ImageNotificationServicegRPCClient() = default;
	~ImageNotificationServicegRPCClient() override = default;

	void StartClient(const std::string& destination) override;
	void StopClient(bool force) override;

	ServiceType GetServiceType() const override;
	const std::string& GetDestination() const override;

	// rpc call UpdateImageDefinition
	CallStatus UpdateImageDefinition(

		const std::string& comId,
		const std::string& imageSourceTitle,
		int32_t width,
		int32_t height) override;

	// rpc call NotifiyImageChanged
	CallStatus NotifiyImageChanged(

		const std::string& comId,
		int32_t x,
		int32_t y,
		int32_t width,
		int32_t height) override;

private:
	std::string m_destination;
	std::shared_ptr<::grpc::ChannelInterface> m_channel;
	std::unique_ptr<::tvimagenotificationservice::ImageNotificationService::Stub> m_stub;
};

} // namespace ImageNotificationService

} // namespace TVRemoteScreenSDKCommunication