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
#include <linux/in.h>
#include <QHeaderView>
#include <QDomDocument>
#include <QStandardPaths>
#include <QFile>
#include <QPushButton>
#include <exception>
#include <QScrollBar>

#include <QDebug>

#include "ProgrammeView.h"
#include "QDomNodeIterator.h"

EpgView::EpgView( const QString& filename ) : viewHours( 32 )
{
	viewBegin.setDate( QDate( 2016, 7, 21 ) );
	viewBegin.setTime( QTime( 22, 0 ) );

	this->setRowCount( viewHours * 60 );
	this->setShowGrid( false );

	this->verticalHeader()->setSectionResizeMode( QHeaderView::Fixed );
	this->verticalHeader()->setDefaultSectionSize( 4 );
	this->horizontalHeader()->setDefaultSectionSize(200);

	this->setEditTriggers( QAbstractItemView::NoEditTriggers );
	this->setSelectionMode( QAbstractItemView::NoSelection );
	
	
	QDomDocument domDoc( "EPGData" );
	QFile file( filename );

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

	std::map<std::string, int> channelList;

	for ( auto node : domDoc.documentElement().elementsByTagName( "channel" ) )
		if ( node.isElement() )
		{
			this->insertColumn( this->columnCount() );
			QTableWidgetItem* hi = new QTableWidgetItem();
			hi->setText( node.toElement().firstChildElement( "display-name" ).text() );
			this->setHorizontalHeaderItem( this->columnCount() - 1, hi );
			channelList.emplace( node.toElement().attribute( "id" ).toStdString(), this->columnCount() - 1 );
		}
		
	for ( auto node : domDoc.documentElement().elementsByTagName( "programme" ) )
	{
		if ( node.isElement() )
		{
			try
			{
				ProgrammeView* pv = new ProgrammeView( node.toElement() );
				int column = channelList.at( node.toElement().attribute( "channel" ).toStdString() );
				this->setCellWidget( viewBegin.secsTo( pv->getStartTime() ) / 60, column, pv );
				this->setSpan( viewBegin.secsTo( pv->getStartTime() ) / 60, column , pv->durationMinutes() , 1 );
			}
			catch( std::out_of_range )
			{
				
			}
		}
	}
}

#include "EpgView.moc"
