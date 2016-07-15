#include <QTableWidget>
#include <QLabel>
#include <QApplication>
#include <QHeaderView>

int main( int argc, char* argv[] )
{
	QApplication app( argc, argv );
	QTableWidget* tv = new QTableWidget();
	tv->setRowCount( 1440 );
	tv->setColumnCount( 3 );
	tv->setShowGrid( false );

	QHeaderView* vh = tv->verticalHeader();
	vh->sectionResizeMode( QHeaderView::Fixed );
	vh->setDefaultSectionSize( 4 );

	QLabel* lbl = new QLabel( "abc" );
	tv->setCellWidget( 1, 1, lbl );

	tv->setSpan( 1, 1, 10, 1 );

	tv->show();
	app.exec();
}
