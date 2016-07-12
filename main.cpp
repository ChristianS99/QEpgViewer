#include <QApplication>
#include "ProgrammeView.h"



int main(int argc, char **argv)
{
	QApplication QEpgViewer(argc, argv);
	ProgrammeView* pv = new ProgrammeView();
	pv->show();
	QEpgViewer.exec();
	return 0;
}
