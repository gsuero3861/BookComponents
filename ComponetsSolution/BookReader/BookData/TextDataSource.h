#include "pch.h"

namespace BookReader
{
	namespace BookData
	{
		[Windows::Foundation::Metadata::WebHostHidden]
		[Windows::UI::Xaml::Data::Bindable]
		public ref class TextDataSource sealed : public BookReader::BookData::BindableSourceBase
		{
		public:
			TextDataSource();

			property Platform::String ^ Title
			{
				void set(Platform::String ^ value) {this->_title =  value ;}
				Platform::String ^ get(){ return this->_title ; }
			}

			property Platform::String ^ Description
			{
				void set(Platform::String ^ value) {this->_description =  value ;}
				Platform::String ^ get(){ return this->_description ; }
			}

		private:

			Platform::String ^ _title ;
			Platform::String ^ _description ;

		};

	}
}