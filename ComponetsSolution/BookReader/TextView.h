#include "pch.h" 

namespace BookReader
{
	public ref class TextView sealed : public Windows::UI::Xaml::Controls::Grid
	{
	public:
		TextView();

		property Platform::Object^ DataSource
		{
			void set(Platform::Object^ value){this->_datasource = (BookData::TextDataSource^)value ;}
			Platform::Object^ get(){ return this->_datasource ; }
		}

	private:
		BookData::TextDataSource^ _datasource ;
	};
}