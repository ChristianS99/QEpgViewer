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
#include <QHeaderView>
#include <QDomDocument>
#include <QStandardPaths>
#include <QFile>
#include <QPushButton>

#include <QDebug>

#include "ProgrammeView.h"
#include "QDomNodeIterator.h"

EpgView::EpgView( ) : viewHours( 32 )
{
	viewBegin.setDate( QDate( 2016, 7, 14 ) );
	viewBegin.setTime( QTime( 22, 0 ) );

	this->setRowCount( viewHours * 60 );
	this->setShowGrid( false );

	this->verticalHeader()->setSectionResizeMode( QHeaderView::Fixed );
	this->verticalHeader()->setDefaultSectionSize( 4 );

	this->setEditTriggers( QAbstractItemView::NoEditTriggers );
	this->setSelectionMode( QAbstractItemView::NoSelection );
}

void EpgView::addChannel( const Channel& newChan )
{
	this->insertColumn( this->columnCount() );
	QTableWidgetItem* hi = new QTableWidgetItem();
	hi->setText( QString( newChan.getDisplayName() ) );
	this->setHorizontalHeaderItem( this->columnCount() - 1, hi );

	QDomDocument domDoc( "ChannelData" );
	QFile file( QStandardPaths::writableLocation( QStandardPaths::AppDataLocation ) + "/" + newChan.getId() + "_2016-07-15.xml" );

	if ( !file.open( QIODevice::ReadOnly ) )
	{
		throw;
	}

	if ( !domDoc.setContent( &file ) )
	{
		file.close();
		throw;
	}

	file.close();

	if ( domDoc.documentElement().tagName() != "tv" )
	{
		throw;
	}

	for ( auto node : domDoc.documentElement().elementsByTagName( "programme" ) )
	{
		if ( node.isElement() )
		{
			ProgrammeView* pv = new ProgrammeView( node.toElement() );
			//qDebug() << pv->startTimeSeconds() / 60 << "," << pv->durationSeconds() / 60;
			this->setCellWidget( viewBegin.secsTo( pv->getStartTime() ) / 60, this->columnCount() - 1, pv );
			this->setSpan( viewBegin.secsTo( pv->getStartTime() ) / 60, this->columnCount() - 1, pv->durationMinutes() , 1 );

			//pv->show();
			//this->setCellWidget( pv->startTimeSeconds() / 60, this->columnCount() - 1, new QPushButton("abc") );
			//this->setSpan( pv->startTimeSeconds() / 60, this->columnCount() - 1, pv->durationSeconds() / 60 , 1 );
			//break;
		}
	}
}

#include "EpgView.moc"
