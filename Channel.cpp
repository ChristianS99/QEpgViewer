/*
 * <one line to give the library's name and an idea of what it does.>
 * Copyright (C) 2016  Christian Schneider <christian@ch-sc.de>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "Channel.h"

#include <QFile>

Channel::Channel(QDomElement channelData) : channelId(""), displayName(""), channelLogoUrl() ,channelLogo()
{
	if ( channelData.tagName() != "channel" )
		{
			throw;
		}
		
	channelId = channelData.attribute( "id" );
	displayName = channelData.firstChildElement("display-name").text();
	channelLogoUrl.setUrl(channelData.firstChildElement("display-name").attribute("src"));
	if( QFile::exists(channelLogoUrl.fileName()) )
		channelLogo.load(channelLogoUrl.fileName());
	//else
		//throw; //not implemented

}

#include "Channel.moc"
