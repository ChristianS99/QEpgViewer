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
	
	EpgView epgView( QStandardPaths::writableLocation( QStandardPaths::AppDataLocation ) + "/programme.xml" );
	//epgView.addChannel( channelList.at( "3sat.de" ) );
	//epgView.addChannel( channelList.at( "zdf.de" ) );

	epgView.show();
	QEpgViewer.exec();
	return 0;
}


