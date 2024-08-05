//********************************************************************************//
// MIT License                                                                    //
//                                                                                //
// Copyright (c) 2021 TeamViewer Germany GmbH                                     //
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
#pragma once

#include <TVRemoteScreenSDKCommunication/ImageService/ServiceFactory.h>
#include <TVRemoteScreenSDKCommunication/ImageService/IImageServiceServer.h>

#include <atomic>
#include <iostream>
#include <memory>
#include <string>

namespace TestImageServicePerformance
{

struct SharedInformation
{
	std::atomic<uint64_t> counter{0};
};

template<TVRemoteScreenSDKCommunication::TransportFramework Framework>
std::shared_ptr<TVRemoteScreenSDKCommunication::ImageService::IImageServiceServer> TestImageService(
	SharedInformation& information,
	const std::string& location)
{
	using namespace TVRemoteScreenSDKCommunication::ImageService;
	const std::shared_ptr<IImageServiceServer> server = ServiceFactory::CreateServer<Framework>();

	const auto receiveFunction = [&information](
		const std::string& /*communicationId*/,
		int32_t /*x*/,
		int32_t /*y*/,
		int32_t /*width*/,
		int32_t /*height*/,
		const std::string& /*pictureData*/,
		const IImageServiceServer::UpdateImageResponseCallback& response)
	{
		++information.counter;
		response(TVRemoteScreenSDKCommunication::CallStatus::Ok);
	};
	server->SetUpdateImageCallback(receiveFunction);

	if (!server->StartServer(location))
	{
		std::cerr << "Error: Failed to start server at location '" << location
			<< "'. Please check that location URL is correct and contains a scheme\n";
		return {};
	}

	return server;
}

} // namespace TestImageServicePerformance
