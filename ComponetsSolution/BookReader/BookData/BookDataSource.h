#include "pch.h"

namespace BookReader
{
	namespace BookData
	{
		[Windows::Foundation::Metadata::WebHostHidden]
		[Windows::UI::Xaml::Data::Bindable]
		public ref class BookDataSource sealed : public BookReader::BookData::BindableSourceBase
		{
		public:
			BookDataSource(); 

			property Platform::String ^ Title
			{
				void set(Platform::String ^ value){this->_title = value ;}
				Platform::String ^ get(){ return this->_title ;}
			}

			property Platform::String ^ BackgroundSource
			{
				void set(Platform::String ^ value){this->_backgrounditemsource = value ;}
				Platform::String ^ get(){ return this->_backgrounditemsource ;}
			}

			property Windows::Foundation::Collections::IVector<ChapterDataSource^>^ Chapters
			{
				void set(Windows::Foundation::Collections::IVector<ChapterDataSource^>^ value) 
				{this->_chapters = value ;}

				Windows::Foundation::Collections::IVector<ChapterDataSource^>^ get(){ return this->_chapters ;}
			}


		private :
			Platform::String ^ _title ;
			Platform::String ^ _backgrounditemsource ;
			Windows::Foundation::Collections::IVector<ChapterDataSource^>^ _chapters ;
		};
	}
}