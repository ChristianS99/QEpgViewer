#include <QApplication>
#include <QDomDocument>
#include <QFile>
#include <QDebug>
#include <QWidget>
#include <QBoxLayout>
#include <QScrollArea>

#include "ProgrammeView.h"



// QDomIterator shamelessly stolen from http://silmor.de/qtstuff.domfor.php (is it open source usable?)
class QDomNodeIterator
{
		int pos;
		const QDomNodeList& container;
	public:
		//constructors and assignments
		QDomNodeIterator ( const QDomNodeList& l, int p ) : pos ( p ), container ( l ) {}
		QDomNodeIterator ( const QDomNodeIterator& ) = default;
		QDomNodeIterator ( QDomNodeIterator&& ) = default;
		QDomNodeIterator& operator= ( const QDomNodeIterator& ) = default;
		QDomNodeIterator& operator= ( QDomNodeIterator && ) = default;

		//increment
		QDomNodeIterator& operator++()
		{
			pos++;
			return *this;
		}

		//comparison
		bool operator== ( const QDomNodeIterator& o )
		{
			return pos == o.pos && container == o.container;
		}
		bool operator!= ( const QDomNodeIterator& o )
		{
			return pos != o.pos || container != o.container;
		}

		//indirection
		QDomNode operator*()
		{
			return container.at ( pos );
		}
};

//begin and end
inline QDomNodeIterator begin ( const QDomNodeList& l )
{
	return QDomNodeIterator ( l, 0 );
}
inline QDomNodeIterator end ( const QDomNodeList& l )
{
	return QDomNodeIterator ( l, l.size() );
}

int main ( int argc, char** argv )
{
	QApplication QEpgViewer ( argc, argv );

	QDomDocument domDoc ( "XMLTv" );
	QFile file ( "3sat.de_2016-07-15.xml" );

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
	
	QScrollArea window;
	QWidget* widget = new QWidget;
	widget->setLayout(new QBoxLayout(QBoxLayout::TopToBottom));
	for ( auto node : domDoc.documentElement().elementsByTagName ( "programme" ) )
		{
			if( node.isElement() )
			{
				ProgrammeView* pv = new ProgrammeView ( node.toElement() );
				widget->layout()->addWidget(pv);
			}
		}
	window.setWidget(widget);
	window.show();
	QEpgViewer.exec();
	return 0;
}
