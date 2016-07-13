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

#include <QBoxLayout>
#include <QLabel>
#include <QDateTime>

#include <QDebug>

ProgrammeView::ProgrammeView ( QDomElement programmeNode )
{
	this->setMouseTracking ( true );
	
	this->setSizePolicy ( QSizePolicy::Expanding, QSizePolicy::Fixed );
	//this->setFixedWidth ( 200 );
	
	this->setFrameStyle( QFrame::Box );
	this->setLineWidth(1);
	
	this->setBackgroundRole(QPalette::Base);
	this->setAutoFillBackground(true);
	
	
	if ( programmeNode.tagName() != "programme" )
		{
			throw;
		}

	QBoxLayout* bl = new QBoxLayout ( QBoxLayout::LeftToRight );
	this->setLayout ( bl );

	QLabel* lblStartTime = new QLabel();
	QDateTime startTime;

	if ( programmeNode.hasAttribute ( "start" ) )
		{
			startTime = QDateTime::fromString ( programmeNode.attribute ( "start" ), "yyyyMMddhhmmss +0200" );
		}

	lblStartTime->setText ( startTime.toString ( "hh:mm" ) );
	bl->addWidget ( lblStartTime, 0, Qt::AlignTop );
	QDateTime endTime;

	if ( programmeNode.hasAttribute ( "stop" ) )
		{
			endTime = QDateTime::fromString ( programmeNode.attribute ( "stop" ), "yyyyMMddhhmmss +0200" );
		}

	this->setFixedHeight ( startTime.secsTo ( endTime ) / 10 );

	QBoxLayout* bl2 = new QBoxLayout ( QBoxLayout::TopToBottom );
	bl2->setAlignment ( Qt::AlignTop );
	bl->addLayout ( bl2, 1 );

	auto titleNode = programmeNode.firstChildElement ( "title" );
	QLabel* lblTitle = new QLabel ( "<noTitle>" );
	lblTitle->setWordWrap ( true );

	QFont fntTitle( lblTitle->font() );
	fntTitle.setBold ( true );
	lblTitle->setFont ( fntTitle );

	if ( !titleNode.isNull() )
		{
			lblTitle->setText ( titleNode.text() );
		}

	bl2->addWidget ( lblTitle );

	auto subTitleNode = programmeNode.firstChildElement ( "sub-title" );

	if ( !subTitleNode.isNull() )
		{
			QLabel* lblSubTitle = new QLabel ( subTitleNode.text() );
			lblSubTitle->setWordWrap ( true );

			QFont fntSubTitle(lblSubTitle->font());
			fntSubTitle.setPointSizeF ( fntSubTitle.pointSizeF() *.9 );
			lblSubTitle->setFont ( fntSubTitle );

			bl2->addWidget ( lblSubTitle );
		}

	auto descriptionNode = programmeNode.firstChildElement ( "desc" );
	QLabel* lblDescripton = new QLabel ( "<noDescription>" );

	QFont fntDescription( lblDescripton->font() );
	fntDescription.setPointSizeF ( fntDescription.pointSizeF() *.8 );
	lblDescripton->setFont ( fntDescription );

	lblDescripton->setWordWrap ( true );

	if ( !descriptionNode.isNull() )
		{
			lblDescripton->setText ( descriptionNode.text() );
		}

	lblDescripton->setAlignment ( Qt::AlignTop );
	bl2->addWidget ( lblDescripton, 1 );
}

void ProgrammeView::enterEvent ( QEvent* e )
{
	this->setBackgroundRole(QPalette::Highlight);

	// don't forget to forward the event
	QWidget::enterEvent ( e );
}

void ProgrammeView::leaveEvent(QEvent* e)
{
	this->setBackgroundRole(QPalette::Base);

	// don't forget to forward the event
	QWidget::leaveEvent ( e );
}


#include "ProgrammeView.moc"
