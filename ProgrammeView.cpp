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

#include "ProgrammeView.h"

#include <QLabel>
#include <QTimeEdit>
#include <QBoxLayout>

ProgrammeView::ProgrammeView() : startTime( 0, 0 )
{
	QBoxLayout* bl = new QBoxLayout ( QBoxLayout::LeftToRight );
	this->setLayout ( bl );

	QLabel* lblTime = new QLabel( startTime.toString("hh:mm"));
	bl->addWidget ( lblTime, 0, Qt::AlignTop );

	QBoxLayout* bl2 = new QBoxLayout ( QBoxLayout::TopToBottom );
	bl->addLayout ( bl2, 1 );

	QLabel* lblTitle = new QLabel ( "Titel\nTitel2" );
	bl2->addWidget ( lblTitle );

	QLabel* lblDescripton = new QLabel ( "Description" );
	bl2->addWidget ( lblDescripton, 1 );
	lblDescripton->setAlignment ( Qt::AlignTop );
	
	
}

ProgrammeView::~ProgrammeView()
{
}

#include "ProgrammeView.moc"
