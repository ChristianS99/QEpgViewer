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

class Ch;
#ifndef CHANNEL_H
#define CHANNEL_H

#include <QString>
#include <QImage>
#include <QDomElement>
#include <QUrl>

class Channel
{
private:
	QString channelId;
	QString displayName;
	QUrl channelLogoUrl;
	QImage channelLogo;
public:
	Channel( QDomElement channelData );
	const QString& getDisplayName() const { return displayName; }; 
};

#endif // CHANNEL_H
