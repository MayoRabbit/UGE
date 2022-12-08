

class Buffer
{

	public:
		Buffer();
		virtual ~Buffer();

		Buffer(const Buffer &) = delete;
		Buffer & operator = (const Buffer &) = delete;

		Buffer(Buffer &&b);
		Buffer & operator = (Buffer &&b);


};
