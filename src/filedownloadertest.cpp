#include <QApplication>
#include <QLabel>

#include "filedownloader.h"

class webImage: public QLabel
{
	Q_OBJECT
private slots:
	void loadImage()
	{
		QPixmap buttonImage;
		buttonImage.loadFromData(downloader->downloadedData());
		this->setPixmap(buttonImage);
	}
private:
	FileDownloader* downloader;
public:
	webImage(QUrl url)
	{
		this->setFixedSize( 200, 200 );
		downloader = new FileDownloader(url, this);
		connect(downloader, SIGNAL (downloaded()), this, SLOT (loadImage()));
	}
};

#include "filedownloadertest.moc"

int main( int argc, char* argv[] )
{
	QApplication app( argc, argv );
	QUrl imageUrl("http://www.socallinuxexpo.org/scale10x-supporting/sites/default/files/styles/medium/public/logos/qt-logo.png");
	webImage main( imageUrl );
	main.show();
	
	//connect(m_pImgCtrl, SIGNAL (downloaded()), this, SLOT (loadImage()));
	
	app.exec();
}
