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

#include "ViewGeometryServiceSocketIOClient.h"

#include <TVRemoteScreenSDKCommunication/ServiceBase/ClientErrorMessage.h>
#include <TVRemoteScreenSDKCommunication/ServiceBase/RequestMetadata.h>

#include "internal/ViewGeometryServiceFunctions.h"

#include "UpdateAreaOfInterestRequest.pb.h"
#include "UpdateAreaOfInterestResponse.pb.h"
#include "UpdateVirtualDesktopRequest.pb.h"
#include "UpdateVirtualDesktopResponse.pb.h"
#include "VirtualDesktop.pb.h"

namespace TVRemoteScreenSDKCommunication
{

namespace ViewGeometryService
{

void ViewGeometryServiceSocketIOClient::StartClient(const std::string& destination)
{
	m_destination = destination;

	m_channel.reset(new Transport::SocketIO::ChannelInterface(m_destination));
}

void ViewGeometryServiceSocketIOClient::StopClient(bool /*force*/)
{
	m_channel.reset();
}

ServiceType ViewGeometryServiceSocketIOClient::GetServiceType() const
{
	return ServiceType::ViewGeometry;
}

const std::string& ViewGeometryServiceSocketIOClient::GetDestination() const
{
	return m_destination;
}

// rpc call UpdateAreaOfInterest
auto ViewGeometryServiceSocketIOClient::UpdateAreaOfInterest(const std::string& comId, const Rect& areaOfInterest) -> UpdateResult
{
	UpdateResult returnValue{};

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

	::tvviewgeometryservice::UpdateAreaOfInterestRequest request{};

	std::unique_ptr<::tvviewgeometryservice::Rect> allocatedRect(new ::tvviewgeometryservice::Rect());

	allocatedRect->set_x(areaOfInterest.x);
	allocatedRect->set_y(areaOfInterest.y);
	allocatedRect->set_width(areaOfInterest.width);
	allocatedRect->set_height(areaOfInterest.height);

	request.set_allocated_areaofinterest(allocatedRect.release());

	::tvviewgeometryservice::UpdateAreaOfInterestResponse response{};

	Transport::SocketIO::Status status = m_channel->Call(comId, Function_UpdateAreaOfInterest, request, response);

	if (status.ok())
	{
		returnValue.state = CallState::Ok;
		returnValue.result = response.result()
				== tvviewgeometryservice::UpdateAreaOfInterestResponse_UpdateAreaOfInterestResult::UpdateAreaOfInterestResponse_UpdateAreaOfInterestResult_Ok
			? UpdateGeometryResult::Ok
			: UpdateGeometryResult::Failed;
	}
	else
	{
		returnValue.errorMessage = status.error_message();
	}
	return returnValue;
}

// rpc call UpdateVirtualDesktop
auto ViewGeometryServiceSocketIOClient::UpdateVirtualDesktop(const std::string& comId,
	const VirtualDesktop& virtualDesktopGeometry) -> UpdateResult
{
	UpdateResult returnValue{};

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

	::tvviewgeometryservice::UpdateVirtualDesktopRequest request{};

	std::unique_ptr<::tvviewgeometryservice::VirtualDesktop> allocatedVD{new ::tvviewgeometryservice::VirtualDesktop()};

	allocatedVD->set_width(virtualDesktopGeometry.width);
	allocatedVD->set_height(virtualDesktopGeometry.height);

	for (const auto& screen : virtualDesktopGeometry.screens)
	{
		// Already owned by the internal container `allocatedVD->screens`
		::tvviewgeometryservice::Screen* allocatedScreen = allocatedVD->add_screens();

		allocatedScreen->set_name(screen.name);

		std::unique_ptr<::tvviewgeometryservice::Rect> allocatedRect{new ::tvviewgeometryservice::Rect()};
		allocatedRect->set_x(screen.geometry.x);
		allocatedRect->set_y(screen.geometry.y);
		allocatedRect->set_width(screen.geometry.width);
		allocatedRect->set_height(screen.geometry.height);

		allocatedScreen->set_allocated_geometry(allocatedRect.release());
	}

	request.set_allocated_virtualdesktopgeometry(allocatedVD.release());

	::tvviewgeometryservice::UpdateVirtualDesktopResponse response{};

	Transport::SocketIO::Status status = m_channel->Call(comId, Function_UpdateVirtualDesktop, request, response);

	if (status.ok())
	{
		returnValue.state = CallState::Ok;
		returnValue.result = response.result()
				== tvviewgeometryservice::UpdateVirtualDesktopResponse_UpdateVirtualDesktopResult::UpdateVirtualDesktopResponse_UpdateVirtualDesktopResult_Ok
			? UpdateGeometryResult::Ok
			: UpdateGeometryResult::Failed;
	}
	else
	{
		returnValue.errorMessage = status.error_message();
	}
	return returnValue;
}

} // namespace ViewGeometryService

} // namespace TVRemoteScreenSDKCommunication