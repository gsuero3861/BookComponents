#include "pch.h"

namespace BookReader
{
	namespace BookData
	{
		[Windows::Foundation::Metadata::WebHostHidden]
		[Windows::UI::Xaml::Data::Bindable]
		public ref class ChapterDataSource sealed : public BookReader::BookData::BindableSourceBase
		{
		public:
			ChapterDataSource();

			property Platform::String^ Title
			{
				void set(Platform::String ^ value){this->_title  = value ;}
				Platform::String ^ get(){ return this->_title ;}
			}

			property TextDataSource^ Text
			{
				void set(TextDataSource^ value){ this->_text =  value ;}
				TextDataSource^ get(){ return this->_text ;}
			}

			property VideoDataSource^ Video
			{
				void set(VideoDataSource^ value){ this->_video = value ;}
				VideoDataSource^ get(){ return this->_video ;}
			}

			property StackDataSource^ Pages
			{
				void set(StackDataSource^ value){ this->_pages =  value ; }
				StackDataSource^ get(){ return this->_pages ;}
			}

			property StackDataSource^ Gallery
			{
				void set(StackDataSource^ value){ this->_gallery =  value ; }
				StackDataSource^ get(){ return this->_gallery ;}
			}

		private:
			Platform::String ^ _title ;
			TextDataSource^ _text ;
			VideoDataSource^ _video ;
			StackDataSource^ _pages ;
			StackDataSource^ _gallery ;
		};
	}
}