#include <iostream>
#include <map>
#include <string>

#include <QApplication>
#include <QDomDocument>
#include <QFile>

#include "EpgView.h"
#include "QDomNodeIterator.h"

int main ( int argc, char** argv )
{
	QApplication QEpgViewer ( argc, argv );
	
	QDomDocument domDoc ( "ChannelList" );
	QFile file ( "channels-Germany.xml" );

	if ( !file.open ( QIODevice::ReadOnly ) )
		return 1;

	if ( !domDoc.setContent ( &file ) )
		{
			file.close();
			return 2;
		}
	file.close();

	if ( domDoc.documentElement().tagName() != "tv" )
		return 3;
	
	EpgView epgView;
	
	std::map<std::string, Channel> channelList;
	for( auto node: domDoc.documentElement().elementsByTagName( "channel" ) )
		if( node.isElement() )
			channelList.emplace( node.toElement().attribute("id").toStdString(), node.toElement() );
	
	//for( auto element: channelList )
	//	std::cout << element.first << " => " << element.second.getDisplayName().toStdString() << std::endl;
		
	epgView.addChannel(channelList.at("3sat.de"));
	epgView.addChannel(channelList.at("zdf.de"));
	
	/*widget->setLayout( new QBoxLayout(QBoxLayout::LeftToRight ));
	
	Channel* channel = new Channel();
	for ( auto node : domDoc.documentElement().elementsByTagName ( "programme" ) )
		{
			if( node.isElement() )
			{
				ProgrammeView* pv = new ProgrammeView ( node.toElement() );
				//connect(pv,SIGNAL(hovered()),pv,SLOT());
				channel->addProgrammeView(pv);
			}
		}
	widget->layout()->addWidget(channel);
	
	Channel* channel2 = new Channel();
	for ( auto node : domDoc.documentElement().elementsByTagName ( "programme" ) )
		{
			if( node.isElement() )
			{
				ProgrammeView* pv = new ProgrammeView ( node.toElement() );
				channel2->addProgrammeView(pv);
			}
		}
	widget->layout()->addWidget(channel2);
	
	QScrollArea window;
	window.setWidget( widget );
	window.show();*/
	epgView.show();
	QEpgViewer.exec();
	return 0;
}
