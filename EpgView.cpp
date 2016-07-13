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

#include "EpgView.h"

#include <QBoxLayout>
#include <QWidget>

EpgView::EpgView()
{
	QWidget* widget = new QWidget();
	QBoxLayout* bl = new QBoxLayout( QBoxLayout::LeftToRight );
	widget->setLayout(bl);
	this->setWidget( widget );
}

void EpgView::addChannel( const Channel& newChannel)
{
	channelList.push_back( newChannel );
}


#include "EpgView.moc"
