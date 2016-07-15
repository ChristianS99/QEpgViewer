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
