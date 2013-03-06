#include "pch.h"

namespace BookReader
{
	namespace BookData
	{
		[Windows::Foundation::Metadata::WebHostHidden]
		[Windows::UI::Xaml::Data::Bindable]
		public ref class VideoDataSource sealed : public BookReader::BookData::BindableSourceBase
		{
		public:
			VideoDataSource();
			property Platform::String ^ ThumbURL
			{
				void set(Platform::String ^ value) {this->_thumburl =  value ;}
				Platform::String ^ get(){ return this->_thumburl ; }
			}

			property Platform::String ^ VideoURL
			{
				void set(Platform::String ^ value) {this->_videourl =  value ;}
				Platform::String ^ get(){ return this->_videourl ; }
			}

		private:

			Platform::String ^ _thumburl ;
			Platform::String ^ _videourl ;


		};
	}
}