#include "pch.h" 

namespace BookReader
{
	public ref class VideoView sealed : public Windows::UI::Xaml::Controls::Grid
	{
	public:
		VideoView();
		property Platform::Object^ DataSource
		{
			void set(Platform::Object^ value){this->_datasource = (BookData::VideoDataSource^)value ;}
			Platform::Object^ get(){ return this->_datasource ; }
		}
	private:
		BookData::VideoDataSource^ _datasource ;
	};
}