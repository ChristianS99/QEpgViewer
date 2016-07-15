#include <map>

#include <QApplication>
#include <QDomDocument>
#include <QFile>
#include <QDir>
#include <QStandardPaths>

#include "EpgView.h"
#include "QDomNodeIterator.h"


int main( int argc, char** argv )
{
	QApplication QEpgViewer( argc, argv );
	QEpgViewer.setApplicationName( "QEpgViewer" );

	QDir dataLocation( QStandardPaths::writableLocation( QStandardPaths::AppDataLocation ) );

	if ( !dataLocation.mkpath( "." ) ) { throw; }

	QDomDocument domDoc( "ChannelList" );
	QFile file( QStandardPaths::writableLocation( QStandardPaths::AppDataLocation ) + "/channels-Germany.xml" );

	if ( !file.open( QIODevice::ReadOnly ) )
	{
		return 1;
	}

	if ( !domDoc.setContent( &file ) )
	{
		file.close();
		return 2;
	}

	file.close();

	if ( domDoc.documentElement().tagName() != "tv" )
	{
		return 3;
	}
	std::map<std::string, Channel> channelList;

	for ( auto node : domDoc.documentElement().elementsByTagName( "channel" ) )
		if ( node.isElement() )
		{
			channelList.emplace( node.toElement().attribute( "id" ).toStdString(), node.toElement() );
		}

	EpgView epgView;
	epgView.addChannel( channelList.at( "3sat.de" ) );
	epgView.addChannel( channelList.at( "zdf.de" ) );

	epgView.show();
	QEpgViewer.exec();
	return 0;
}


